#include "audiorecorder.h"

// Global buffers
#include "global.h"

AudioRecorder::AudioRecorder(QObject *parent) :
    QObject(parent)
{

    // Setup buffer
    m_AudioData = new QBuffer();

    //QTimer::singleShot(2000, this, SLOT(stopRecording()));
    connect(m_AudioData,SIGNAL(readyRead()),this,SLOT(measureAudioBytes()));

    // Begin recording
    startRecording();

}

void AudioRecorder::startRecording()
{

    qDebug() << "Starting Audio recording...";
    qDebug() << "Opening audio input buffer: " << m_AudioData->open( QIODevice::WriteOnly | QIODevice::Truncate );

    // Setup Audio Format
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

//    foreach (const QAudioDeviceInfo &deviceInfo,  QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
//        qDebug() << "Audio Output Device name: " << deviceInfo.deviceName();
//    }
//    foreach (const QAudioDeviceInfo &deviceInfo,  QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
//        qDebug() << "Audio Input Device name: " << deviceInfo.deviceName();
//    }

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    qDebug() << "Input device was: " << info.deviceName();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported try to use nearest...";
        format = info.nearestFormat(format);
    }

    m_AudioInput = new QAudioInput(format, this);
    qDebug() << "Begin recording now...";
    m_AudioInput->start(m_AudioData);

}

void AudioRecorder::measureAudioBytes()
{

    qDebug() << "QBuffer Has this many bytes: " << m_AudioData->size();

    // Take the data from the internal QBuffer QBytearray
    QByteArray dataToWrite = m_AudioData->buffer();
    //qDebug() << "QByteArray Has this many bytes: " << dataToWrite.size();

    // Push data into audio buffer
    char readByte;
    for (int i = 0; i < dataToWrite.size(); ++i) {
        int subscript = i % MAX_BUFFER_SIZE;
        readByte = dataToWrite.at(i);
//        if ( readByte > 0 ) {
//            qDebug() << "Write: " << readByte;
//        }
        //fprintf(stderr, "Write: %c\n", buffer[i % MAX_BUFFER_SIZE]);
        freeBytes.acquire();
        buffer[subscript] = readByte;
        usedBytes.release();
    }

    // Cleanout the buffer
    m_AudioData->buffer().remove(0,m_AudioData->size());

    //qDebug() << "Cleaned QBuffer Has this many bytes: " << m_AudioData->size();

}

void AudioRecorder::stopRecording()
{
    qDebug() << "Stopping Audio recording...";
    m_AudioInput->stop();
    m_AudioData->close();
    delete m_AudioInput;
}

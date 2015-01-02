#ifndef CONSUMER_H
#define CONSUMER_H

#include <QCoreApplication>
#include <QObject>
#include <QThread>
#include <QTime>
#include "global.h"
#include <stdio.h>

/// Testing
#include <QFile>

/// Play audio
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QDebug>
#include <QAudioOutput>
#include <QBuffer>

class Consumer : public QThread
{
    Q_OBJECT
public:

//    QFile inputFile;
//    QAudioOutput *audioOutput;

    void run()
    {

        // Setup Audio Format
        qDebug() << "Setting up audio output...";
        QAudioFormat format;
        format.setSampleRate(48000);
        format.setChannelCount(1);
        format.setSampleSize(16);
        format.setCodec("audio/pcm");
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleType(QAudioFormat::SignedInt);

//        foreach (const QAudioDeviceInfo &deviceInfo,  QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
//            qDebug() << "Audio Output Device name: " << deviceInfo.deviceName();
//        }
//        foreach (const QAudioDeviceInfo &deviceInfo,  QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
//            qDebug() << "Audio Input Device name: " << deviceInfo.deviceName();
//        }

        qDebug() << "Beginning audio playback...";
        QBuffer outputBuffer;
        QAudioOutput *audioOutput = new QAudioOutput(format);

        QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
        qDebug() << "Output device was: " << info.deviceName();
        if ( !info.isFormatSupported(format) ) {
            qWarning() << "Raw audio format not supported by backend, cannot play audio.";
            return;
        }

        int counter = 0;
        QByteArray capturedData;
        while ( counter < 2048000 ) {
            usedBytes.acquire();
            qint16 data = buffer[counter % MAX_BUFFER_SIZE];
            char upper = ( data & 0xFF00 ) >> 8;
            char lower = ( data & 0x00FF );
            //qDebug() << "Upper: " << (int)upper << " Count: " << counter;
            //qDebug() << "Lower: " << (int)lower << " Count: " << counter;
            capturedData.append(upper);
            capturedData.append(lower);
            freeBytes.release();
            counter++;
        }
        fprintf(stderr, "\n");

        qDebug() << "Copy Buffer";

        outputBuffer.setBuffer(&capturedData);

        qDebug() << "Opening audio output buffer: " << outputBuffer.open( QIODevice::ReadOnly );

        qDebug() << "Start Playing";

        // Start playing
        audioOutput->start(&outputBuffer);

//        inputFile.setFileName("/home/pi/Front_Center.wav");
//        qDebug() << inputFile.open(QIODevice::ReadOnly);

//        QAudioFormat format;
//        // Set up the format, eg.
//        format.setSampleRate(8000);
//        format.setChannelCount(1);
//        format.setSampleSize(8);
//        format.setCodec("audio/pcm");
//        format.setByteOrder(QAudioFormat::LittleEndian);
//        format.setSampleType(QAudioFormat::UnSignedInt);

//        QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
//        if (!info.isFormatSupported(format)) {
//            qDebug()<<"raw audio format not supported by backend, cannot play audio.";
//            return;
//        }

//        audioOutput = new QAudioOutput(format);
//        connect(audioOutput,SIGNAL(stateChanged(QAudio::State)),SLOT(finishedPlaying(QAudio::State)));
//        audioOutput->start(&inputFile);

    }

signals:
    void stringConsumed(const QString &text);

public slots:

    void finishedPlaying(QAudio::State state) {

        qDebug() << "Finished Playing: " << state;

    }

protected:
    bool finish;
};

#endif // CONSUMER_H

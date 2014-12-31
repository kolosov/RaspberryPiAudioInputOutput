#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QBuffer>
#include <QDebug>
#include <QTimer>

#include <QAudio>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioDeviceInfo>

class AudioRecorder : public QObject
{
    Q_OBJECT
public:
    explicit AudioRecorder(QObject *parent = 0);

    void startRecording();

private:

    QBuffer *m_AudioData;
    QAudioInput *m_AudioInput;

signals:

private slots:

    void stopRecording();

    void measureAudioBytes();

};

#endif // AUDIORECORDER_H

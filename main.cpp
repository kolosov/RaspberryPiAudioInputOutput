#include <QCoreApplication>
#include <Consumer.h>
#include <Producer.h>
#include <audiorecorder.h>

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    // This will be the producer
    AudioRecorder *recorder = new AudioRecorder();

//    Producer producer;
    Consumer consumer;
//    producer.start();
    consumer.start();
//    producer.wait();
//    consumer.wait();

    return a.exec();

}

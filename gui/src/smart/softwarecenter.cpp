#include "softwarecenter.h"

#include <QLocalSocket>
#include <QStringLiteral>
#include <QByteArray>
#include <QTextCodec>
#include <QRegExp>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QQmlContext>
#include <QJsonArray>

namespace smart {

/**
 * @brief SoftwareCenter::SoftwareCenter
 * @param serverSocket
 */
SoftwareCenter::SoftwareCenter(QString serverSocket)
{
    mServerSocket = serverSocket;
}

/**
 * @brief SoftwareCenter::loadInstalledPrograms
 * @return
 */
QVariantList  SoftwareCenter::loadInstalledPrograms()
{
    QJsonDocument jsonObject;

    QLocalSocket socket;
    socket.connectToServer(mServerSocket);

    if(socket.waitForConnected()){
        qDebug("Connected");

        auto request = QStringLiteral("GET /v2/snaps HTTP/1.1\r\nHost: localhost\r\nUser-Agent: Go-http-client/1.1\r\nX-Allow-Interaction: true\r\nAccept-Encoding: gzip\r\n\r\n");

        qint64 numBytesWritten = 0;

        auto payload = request.toUtf8();

        int payloadSize = payload.size();

        while ((numBytesWritten = socket.write(payload)) != payloadSize) {
            numBytesWritten += numBytesWritten;
        }

        if(socket.isReadable()){
            if(socket.waitForReadyRead()){

                QStringList tokens = QString(socket.readLine()).split(QRegExp("[ \r\n][ \r\n]*"));

                if(tokens.size() == 4 && tokens[2] == "OK"){
                    QString tmp;
                    while (socket.canReadLine()
                           && !QString(socket.readLine()).startsWith("\r\n")) {
                    }

                    auto lineWithChunkSize = socket.readLine();
                    bool bStatus = false;
                    auto chunkSize = lineWithChunkSize.toUInt(&bStatus,16);
                    auto jsonString = socket.read(chunkSize);

                    QJsonParseError error;
                    jsonObject = QJsonDocument::fromJson(jsonString, &error);

                    if(jsonObject.isNull()){
                        qDebug() << "Not a valid JSON"
                                 << error.errorString();


                    } else {
                        return jsonObject["result"].toArray().toVariantList();
                    }
                } else {
                    qDebug("Server return with erro");
                }
            } else {
                qDebug("Socket read timeout");
            }
        } else {
            qDebug("Not able to read from Socket");
        }

        if (socket.waitForDisconnected(1000)){
            qDebug("Disconnected!");
        }

    } else {
        qDebug("Connection timeout.");
    }

    return QVariantList();
}

}

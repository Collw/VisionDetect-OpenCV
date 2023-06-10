//criado e desenvolvido por welabs
#include <iostream>
#include <clocale>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {

    setlocale(LC_ALL, "Portuguese");

    // Carregando o arquivo de modelo pr�-treinado para detec��o facial
    CascadeClassifier face_cascade;
    face_cascade.load("C:\\Users\\Usu�rio\\Documents\\opencvfiles\\data\\haarcascades\\haarcascade_frontalface_default.xml");

    // Carregando o arquivo de modelo pr�-treinado para detec��o de m�os
    CascadeClassifier hand_cascade;
    hand_cascade.load("C:\\Users\\Usu�rio\\Documents\\opencvfiles\\data\\haarcascades\\hand.xml");

    // Carregando o arquivo de modelo pr�-treinado para detec��o de m�os abertas
    CascadeClassifier palm_cascade;
    palm_cascade.load("C:\\Users\\Usu�rio\\Documents\\opencvfiles\\data\\haarcascades\\palm.xml");

    // Iniciando a captura de v�deo
    VideoCapture cap(1);
    if (!cap.isOpened()) {
        std::cout << "\n\n\nN�o foi possivel acessar sua camera. Tente mudar o parametro para um numero anterior ou seguinte." << endl;
        return -1;
    }

    Mat frame;
    bool detectFacesEnabled = true;
    bool detectHandsEnabled = true;

    while (cap.read(frame)) {
        // Redimensionar o quadro para uma resolu��o menor
        const double scale = 0.5; // Fator de escala para redu��o de resolu��o
        resize(frame, frame, Size(), scale, scale);

        // Convertendo o quadro redimensionado para escala de cinza
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Detectando faces no quadro
        std::vector<Rect> faces;
        if (detectFacesEnabled) {
            face_cascade.detectMultiScale(gray, faces, 1.3, 5);
        }

        // Imprimindo informa��es sobre as faces detectadas
        cout << "faces detected: " << faces.size() << endl;

        // Desenhando ret�ngulos e adicionando tags nas faces detectadas
        for (const auto& face : faces) {
            rectangle(frame, face, Scalar(0, 255, 0), 2);
            string tag = "Face";
            Point tagPosition(face.x, face.y - 5);
            putText(frame, tag, tagPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
        }

        // Detectando m�os no quadro
        std::vector<Rect> hands;
        if (detectHandsEnabled) {
            hand_cascade.detectMultiScale(gray, hands, 1.1, 3);
        }

        // Imprimindo informa��es sobre as m�os fechadas detectadas
        cout << "Close Hands detected: " << hands.size() << endl;

        // Desenhando ret�ngulos e adicionando tags nas m�os detectadas
        for (const auto& hand : hands) {
            rectangle(frame, hand, Scalar(255, 0, 0), 2);
            string tag = "Closed Hand";
            Point tagPosition(hand.x, hand.y - 5);
            putText(frame, tag, tagPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);
        }

        // Detectando m�os abertas no quadro
        std::vector<Rect> palms;
        if (detectHandsEnabled) {
            palm_cascade.detectMultiScale(gray, palms, 1.1, 3);
        }

        // Imprimindo informa��es sobre as m�os abertas detectadas
        cout << "Open Hands detected: " << palms.size() << endl;

        // Desenhando ret�ngulos e adicionando tags nas m�os abertas detectadas
        for (const auto& palm : palms) {
            rectangle(frame, palm, Scalar(255, 0, 0), 2);
            string tag = "Open Hand";
            Point tagPosition(palm.x, palm.y - 5);
            putText(frame, tag, tagPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);
        }

        // Exibindo o quadro resultante
        imshow("OrangeDetection", frame);

        // Verificar tecla pressionada
        char key = waitKey(1);
        if (key == 'q') {
            break;
        }
        else if (key == 'f') {
            detectFacesEnabled = !detectFacesEnabled;
            cout << "Detec��o de faces: " << (detectFacesEnabled ? "Ativada" : "Desativada") << endl;
        }
        else if (key == 'h') {
            detectHandsEnabled = !detectHandsEnabled;
            cout << "Detec��o de m�os: " << (detectHandsEnabled ? "Ativada" : "Desativada") << endl;
        }
    }

    // Liberando os recursos
    cap.release();
    destroyAllWindows();

    return 0;
}

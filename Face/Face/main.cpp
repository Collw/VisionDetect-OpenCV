// Código desenvolvido por welabs: www.welabs.tech
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

    CascadeClassifier face_cascade;
    face_cascade.load("C:\\Users\\Usuário\\Documents\\opencvfiles\\data\\haarcascades\\haarcascade_frontalface_default.xml");

    CascadeClassifier hand_cascade;
    hand_cascade.load("C:\\Users\\Usuário\\Documents\\opencvfiles\\data\\haarcascades\\hand.xml");

    CascadeClassifier palm_cascade;
    palm_cascade.load("C:\\Users\\Usuário\\Documents\\opencvfiles\\data\\haarcascades\\palm.xml");

    VideoCapture cap(1);
    if (!cap.isOpened()) {
        std::cout << "\n\n\nNão foi possivel acessar sua camera. Tente mudar o parametro para um numero anterior ou seguinte." << endl;
        return -1;
    }

    Mat frame;
    bool detectFacesEnabled = true;
    bool detectHandsEnabled = true;

    while (cap.read(frame)) {
        const double scale = 0.5;
        resize(frame, frame, Size(), scale, scale);

        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        std::vector<Rect> faces;
        if (detectFacesEnabled) {
            double scaleFactor = 1.1;
            int minNeighbors = 3;
            int minSize = 30;
            int maxSize = 300;
            face_cascade.detectMultiScale(gray, faces, scaleFactor, minNeighbors, 0, Size(minSize, minSize), Size(maxSize, maxSize));
        }

        cout << "Faces detected: " << faces.size() << endl;

        for (const auto& face : faces) {
            rectangle(frame, face, Scalar(0, 255, 0), 2);
            string tag = "Face";
            Point tagPosition(face.x, face.y - 5);
            putText(frame, tag, tagPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
        }

        std::vector<Rect> hands;
        if (detectHandsEnabled) {
            double scaleFactor = 1.05;  // Ajuste o fator de escala
            int minNeighbors = 5;       // Ajuste o número mínimo de vizinhos
            int minSize = 50;           // Ajuste o tamanho mínimo da mão
            hand_cascade.detectMultiScale(gray, hands, scaleFactor, minNeighbors, 0, Size(minSize, minSize));
        }

        cout << "Hands detected: " << hands.size() << endl;

        for (const auto& hand : hands) {
            rectangle(frame, hand, Scalar(0, 0, 255), 2);
            string tag = "Hand";
            Point tagPosition(hand.x, hand.y - 5);
            putText(frame, tag, tagPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);
        }

        std::vector<Rect> palms;
        if (detectHandsEnabled) {
            double scaleFactor = 1.05;  // Ajuste o fator de escala
            int minNeighbors = 5;       // Ajuste o número mínimo de vizinhos
            int minSize = 50;           // Ajuste o tamanho mínimo da mão aberta
            palm_cascade.detectMultiScale(gray, palms, scaleFactor, minNeighbors, 0, Size(minSize, minSize));
        }

        cout << "Palms detected: " << palms.size() << endl;

        for (const auto& palm : palms) {
            rectangle(frame, palm, Scalar(255, 0, 0), 2);
            string tag = "Palm";
            Point tagPosition(palm.x, palm.y - 5);
            putText(frame, tag, tagPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);
        }

        imshow("Detection", frame);

        char key = waitKey(1);
        if (key == 'q') {
            break;
        }
        else if (key == 'f') {
            detectFacesEnabled = !detectFacesEnabled;
            cout << "Detecção de faces: " << (detectFacesEnabled ? "Ativada" : "Desativada") << endl;
        }
        else if (key == 'h') {
            detectHandsEnabled = !detectHandsEnabled;
            cout << "Detecção de mãos: " << (detectHandsEnabled ? "Ativada" : "Desativada") << endl;
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}

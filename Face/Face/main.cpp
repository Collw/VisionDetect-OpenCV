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

    // Carregando o arquivo de modelo pré-treinado para detecção facial
    CascadeClassifier face_cascade;
    face_cascade.load("C:\\Users\\Usuário\\Documents\\opencvfiles\\data\\haarcascades\\haarcascade_frontalface_default.xml");

    // Carregando o arquivo de modelo pré-treinado para detecção de mãos
    CascadeClassifier hand_cascade;
    hand_cascade.load("C:\\Users\\Usuário\\Documents\\opencvfiles\\data\\haarcascades\\hand.xml");

    // Carregando o arquivo de modelo pré-treinado para detecção de mãos abertas
    CascadeClassifier palm_cascade;
    palm_cascade.load("C:\\Users\\Usuário\\Documents\\opencvfiles\\data\\haarcascades\\palm.xml");

    // Iniciando a captura de vídeo
    VideoCapture cap(1);//caso de o erro -1 no console, mude a variael 'cap' para 0 ou 2, ex:  VideoCapture cap(0) ou  VideoCapture cap(2). 
    if (!cap.isOpened()) {
        std::cout << "\n\n\nNão foi possivel acessar sua camera. Tente mudar o parametro para um numero anterior ou seguinte." << endl;
        return -1;
    }

    Mat frame;
    bool detectFacesEnabled = true;
    bool detectHandsEnabled = true;

    while (cap.read(frame)) {
        // Redimensionar o quadro para uma resolução menor
        const double scale = 0.5; // Fator de escala para redução de resolução
        resize(frame, frame, Size(), scale, scale);

        // Convertendo o quadro redimensionado para escala de cinza
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Detectando faces no quadro
        std::vector<Rect> faces;
        if (detectFacesEnabled) {
            face_cascade.detectMultiScale(gray, faces, 1.3, 5);
        }

        // Imprimindo informações sobre as faces detectadas
        cout << "faces detected: " << faces.size() << endl;

        // Desenhando retângulos e adicionando tags nas faces detectadas
        for (const auto& face : faces) {
            rectangle(frame, face, Scalar(0, 255, 0), 2);
            string tag = "Face";
            Point tagPosition(face.x, face.y - 5);
            putText(frame, tag, tagPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
        }

        // Detectando mãos no quadro
        std::vector<Rect> hands;
        if (detectHandsEnabled) {
            hand_cascade.detectMultiScale(gray, hands, 1.1, 3);
        }

        // Imprimindo informações sobre as mãos fechadas detectadas
        cout << "Close Hands detected: " << hands.size() << endl;

        // Desenhando retângulos e adicionando tags nas mãos detectadas
        for (const auto& hand : hands) {
            rectangle(frame, hand, Scalar(255, 0, 0), 2);
            string tag = "Closed Hand";
            Point tagPosition(hand.x, hand.y - 5);
            putText(frame, tag, tagPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);
        }

        // Detectando mãos abertas no quadro
        std::vector<Rect> palms;
        if (detectHandsEnabled) {
            palm_cascade.detectMultiScale(gray, palms, 1.1, 3);
        }

        // Imprimindo informações sobre as mãos abertas detectadas
        cout << "Open Hands detected: " << palms.size() << endl;

        // Desenhando retângulos e adicionando tags nas mãos abertas detectadas
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
            cout << "Detecção de faces: " << (detectFacesEnabled ? "Ativada" : "Desativada") << endl;
        }
        else if (key == 'h') {
            detectHandsEnabled = !detectHandsEnabled;
            cout << "Detecção de mãos: " << (detectHandsEnabled ? "Ativada" : "Desativada") << endl;
        }
    }

    // Liberando os recursos
    cap.release();
    destroyAllWindows();

    return 0;
}

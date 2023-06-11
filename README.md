# Visão computacional de Detecção de Rostos e Mãos

Este projeto implementa um programa em C++ que utiliza a biblioteca OpenCV para realizar a detecção de rostos, mãos fechadas e mãos abertas em tempo real a partir de uma captura de vídeo da câmera.

## Descrição

O programa utiliza arquivos de modelo pré-treinados em formato XML para realizar a detecção dos objetos. O modelo para detecção de rostos é baseado no algoritmo Haar Cascade, enquanto os modelos para detecção de mãos fechadas e mãos abertas são específicos para cada caso.

O programa exibe o vídeo capturado pela câmera em tempo real, destacando os rostos detectados em verde, as mãos fechadas em azul e as mãos abertas em vermelho. Também são exibidas informações sobre a quantidade de rostos, mãos fechadas e mãos abertas detectadas.

## Pré-requisitos

- OpenCV: Certifique-se de ter o OpenCV instalado em seu sistema. Você pode baixar a biblioteca no site oficial do OpenCV (https://opencv.org/) e seguir as instruções de instalação para a sua plataforma específica.

## Configuração

Antes de executar o programa, é necessário realizar algumas configurações:

1. Atualizar os caminhos dos arquivos XML: No código-fonte fornecido, existem três variáveis que armazenam os caminhos dos arquivos XML dos modelos pré-treinados. É necessário atualizar esses caminhos para apontar para os arquivos correspondentes em seu sistema.

2. Compilar o código: Utilize um ambiente de desenvolvimento C++ compatível para compilar o código-fonte. Certifique-se de incluir a biblioteca OpenCV e configurar as opções de compilação adequadamente.

## Utilização

Após realizar as configurações necessárias e compilar o código, execute o programa. A câmera será ativada e você poderá visualizar o vídeo em tempo real com as detecções de rostos, mãos fechadas e mãos abertas destacadas. As informações sobre a quantidade de objetos detectados serão exibidas no console.

Você pode pressionar as seguintes teclas durante a execução do programa:

- 'q': Encerra a execução do programa.
- 'f': Ativa/desativa a detecção de rostos.
- 'h': Ativa/desativa a detecção de mãos.

## Contribuição

Contribuições são bem-vindas! Se você encontrar algum problema ou tiver sugestões para melhorias, sinta-se à vontade para abrir uma issue ou enviar um pull request.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE). Sinta-se à vontade para usá-lo, modificar e distribuir conforme necessário.

Espero que este assistente de detecção de rostos e mãos seja útil para você! Se tiver alguma dúvida, não hesite em entrar em contato.

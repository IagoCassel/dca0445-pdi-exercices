# Primeira Unidade

## Exercício 1

Como primeiro exercício foi pedido que escrevêssemos um código simples para mostrar uma imagem PNG em uma janela do OpenCV. Para isso, foi usado este código abaixo:

```
#include <iostream>
#include "opencv2/opencv.hpp"


int main(int argc, char** argv) {
	cv::Mat image;
	image = cv::imread("biel.png", cv::IMREAD_GRAYSCALE);
	cv::imshow("image", image);
	cv::waitKey();
	return 0;
}
```

Este código pega a imagem *biel.png* e mostra em uma janela chamada "image". Para isso, criamos uma imagem usando o tipo *cv::Mat*, carregamos essa imagem do tipo descrito com o PNG em questão, usando o *cv::imread("biel.png", cv::IMREAD_GRAYSCALE)*. Note que estamos pegando a imagem em modo monocromático, em tons de cinza, pelo *cv::IMREAD_GRAYSCALE*. Por fim, mostramos a imagem através da função *cv::imshow("image", image);*. Dessa forma, o resultado desse algoritmo mostra:

<p align="center">
  <img src="https://user-images.githubusercontent.com/48588172/145676678-9af82952-1cd0-484e-9a14-e12aeac36e7a.png" />
</p>

## Exercício 2.1

Para imagem do exemplo anterior, foi pedido que implementássemos um algoritmo que recebesse as coordenadas de dois pontos, **P1** e **P2**. Tendo as coordenadas *(x,y)* desses pontos, a imagem resultante deve ser a mesma imagem *biel.png* com uma porção de sua composição sendo modificada para representar os valores negativos daquela imagem. A porção da imagem deve ser o retângulo formado entre os pontos **P1** e **P2**, tal que que o segmento reta que conecta esses pontos seja a diagonal desse retângulo.

Antes de realizar o processo, foi implementado uma condição de erro para o carregamento da imagem. Esse trecho de código foi adicionado para garantir que a imagem seja aberta corretamente no código. Caso não seja aberta corretamente, o sistema alerta o usuário e finaliza a função com erro.

```
    Mat image;

    image = imread("biel.png", IMREAD_GRAYSCALE);
    if (!image.data) {
        cout << "nao abriu biel.png" << endl;
        return -1;
    }
```

Para realizar a inversão dos valores na imagem, dentro do retângulo definido pelo usuário, basta colhermos essas coordenadas e realizar um duplo *for*, que varrerá da coordenada y do **P1** até a coordenada y do **P2**, para cada y que vai do y do **P1** até o y do **P2**. Para cada pixel, fazemos com que seu novo valor de [0,255] seja 255 subtraído de seu valor prévio. Assim, isso resulta no código:

```
    cout << "Escolha o X do p1: ";
    cin >> x1;

    cout << "Escolha o Y do p1: ";
    cin >> y1;

    cout << "Escolha o X do p2: ";
    cin >> x2;

    cout << "Escolha o Y do p2: ";
    cin >> y2;

    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
        }
    }
```

Por fim, mostramos a imagem em uma janela e guardamos seu resultado em um PNG com a função *imwrite("invertido.png", image);*.

```
    imwrite("invertido.png", image);
```

A janela do programa deve retornar a imagem, para **P1** = (50,50) e **P2** = (200,200):

<p align="center">
  <img src="https://user-images.githubusercontent.com/48588172/145677211-60d21d15-4a65-4be4-8959-d0b191eb0898.png" />
</p>

## Exercício 2.2

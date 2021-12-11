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

Este código pega a imagem *biel.png* e mostra em uma genela chamada "image". Para isso, crimamos uma imagem usando o tipo *cv::Mat*, carregamos essa imagem do tipo descrito com o PNG em questão, usando o *cv::imread("biel.png", cv::IMREAD_GRAYSCALE)*. Note que estamos pegando a imagem em modo monocromático, em tons de cinza, pelo *cv::IMREAD_GRAYSCALE*. Por fim, mostramos a imagem através da função *cv::imshow("image", image);*. Dessa forma, o resultado desse algorítmo mostra:

![1](https://user-images.githubusercontent.com/48588172/145676678-9af82952-1cd0-484e-9a14-e12aeac36e7a.png)

## Exercício 2.1

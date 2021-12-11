# Primeira Unidade

## Exercício 1

*Como primeiro exercício foi pedido que escrevesemos um código simples para mostar uma imagem PNG em uma janela do OpenCV. Para isso, foi usado este código abaixo:*

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

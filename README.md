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

Nesse exercício devemos aplicar um algoritmo que embaralhe uma imagem, com partições de área iguais da imagem. Para uma imagem quadrada, devemos dividir ela em quatro quadrados iguais representando os quadrantes daquela imagem. Assim, tendo os quatro quadrantes, devemos embaralhar eles na imagem, de forma que a imagem resultante seja uma ordem aleatória dos quatro quadrantes.

Para isso, começamos dando *input* na imagem escolhida e criando uma cópia dela, que será sua versão embaralhada. Esse trecho do código de encontra abaixo:

```
    Mat image;
    image = imread("biel.png", IMREAD_GRAYSCALE);
    if (!image.data) {
        cout << "nao abriu biel.png" << endl;
        return -1;
    }
    Mat embaralhada = image.clone();
```

Após isso, devemos particionar a imagem nos seus quarto quadrantes. Afim disso, calculamos o ponto central da imagem de tal forma:

```
    int largura_central = image.cols/2;
    int altura_central = image.rows/2;
```

Tendo essas coordenadas centrais, podemos delimitar a área dos quadrantes dessa forma:

```
    Rect region_array[4];
    region_array[0] = Rect(0, 0, largura_central, altura_central);
    region_array[1] = Rect(largura_central, 0, largura_central, altura_central);
    region_array[2] = Rect(0, altura_central, largura_central, altura_central);
    region_array[3] = Rect(largura_central, altura_central, largura_central, altura_central);
    
```

Passamos o conteúdo do imagem para sua respectiva região:

```
    Mat im0 = image(region_array[0]);
    Mat im1 = image(region_array[1]);
    Mat im2 = image(region_array[2]);
    Mat im3 = image(region_array[3]);
```

Agora nós temos quatro partes da imagem guardadas nas variáveis *im0, im1, im2* e *im3*. Para embaralhar elas na imagem resultante, temos que criar um algoritmo capaz de randomizar a ordem de construção da imagem original. Para isso utilizaremos essa rotina:

```
    int order_array[4] = { 0 , 1 , 2 , 3 };
    shuffle(begin(order_array), end(order_array), default_random_engine(system_clock::now().time_since_epoch().count()));
```

Essa rotina define a ordem (0, 1, 2, 3), que é logo embaralhada pela função *shuffle*, do próprio C++. Vale a pena cita que o termo *default_random_engine(system_clock::now().time_since_epoch().count()* usa tanto a biblioteca <chrono> quanto <random>. Esse termo server de semente randomizada pelo *timer* do próprio computador, que entra como *input* da função *shuffle* (mais informações, visitar a documentação oficial do *shuffle*, *chrono* e *random*). Então o início do código deve incluir:

```
#include <random> 
using namespace chrono;
```

Finalmente, tendo a ordem de contrução do array *order_array* randomizada, podemos construir a nova imagem de forma a randomizar o posicionamento dos quadrantes. Para isso, copiamos essas partições para a nova imagem.

```
    im0.copyTo(embaralhada(region_array[order_array[0]]));
    im1.copyTo(embaralhada(region_array[order_array[1]]));
    im2.copyTo(embaralhada(region_array[order_array[2]]));
    im3.copyTo(embaralhada(region_array[order_array[3]]));

    cv::imshow("embaralhado", embaralhada);
    cv::imwrite("embaralhado.png", embaralhada);
    cv::waitKey();
```

Com isso, exemplos de resultados que podemos ter são:

<p align="center">
  <img align="left" src="https://user-images.githubusercontent.com/48588172/145681073-f447e27c-08a7-4249-b069-217c4c4f7c29.png" /><img src="https://user-images.githubusercontent.com/48588172/145681084-33253165-d158-42c2-b7ac-9608df919e74.png" /><img align="right" src="https://user-images.githubusercontent.com/48588172/145681091-c73e4e8f-e8e9-4b5d-a274-22585c72368a.png" />					
</p>
	
## Exercício 3.1

Nesta questão foi proposto que nós verifiquemos o porquê da variável *nobjects* possuir um problema na rotulação, quando seu valor passa de 255. O código apresentado é:
	
```
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  cv::Mat image, realce;
  int width, height;
  int nobjects;
  
  cv::Point p;
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }

  width=image.cols;
  height=image.rows;
  std::cout << width << "x" << height << std::endl;

  p.x=0;
  p.y=0;

  // busca objetos presentes
  nobjects=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
        // achou um objeto
        nobjects++;
        p.x=j;
        p.y=i;
  		// preenche o objeto com o contador
		  cv::floodFill(image,p,nobjects);
      }
    }
  }
  std::cout << "a figura tem " << nobjects << " bolhas\n";
  cv::equalizeHist(image, realce);
  cv::imshow("image", image);
  cv::imshow("realce", realce);
  cv::imwrite("labeling.png", image);
  cv::waitKey();
  return 0;
}
```

Com uma rápida visualização, é possível perceber que o problema está no *input* da função *cv::floodFill(image,p,nobjects)*. No caso, esse *nobjects* não pode passar de 255. Para isso, podemos resolver esse problema passando não o *nobjects* como *input* da função, mas sim o resto da divisão do *nobjects* com 256, ou seja *nobjects % 256*. Assim:
	
* Caso *nobjects = 149*: *nobjects % 256 = 149*;
* Caso *nobjects = 255*: *nobjects % 256 = 255*;
* Caso *nobjects = 256*: *nobjects % 256 = 0*;
* Caso *nobjects = 257*: *nobjects % 256 = 1*;
* Caso *nobjects = 321*: *nobjects % 256 = 65*.	

**(Não necessário)** Ainda, caso não seja desejável que entremos com o *input = 0* no *floodFill* podemos alterar o código para *(nobjects % 256) + (1 & (nobjects > 255))*. Assim o sistema retornaria:

* Caso *nobjects = 149*: *(nobjects % 256) + (1 & (nobjects > 255)) = 149*;
* Caso *nobjects = 255*: *(nobjects % 256) + (1 & (nobjects > 255)) = 255*;
* Caso *nobjects = 256*: *(nobjects % 256) + (1 & (nobjects > 255)) = 1*;
* Caso *nobjects = 257*: *(nobjects % 256) + (1 & (nobjects > 255)) = 2*;
* Caso *nobjects = 321*: *(nobjects % 256) + (1 & (nobjects > 255)) = 66*.

A mudança no código ficaria:
	
```
cv::floodFill(image, p, nobjects % 256);
```

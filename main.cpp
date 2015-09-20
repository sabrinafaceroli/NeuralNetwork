#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;


//Calcula o net dos neurônios
double net(double peso[4], int A, int B, int indA, int indB)
{
	double n;
	n = (peso[indA]*A) + 1;
	n = (peso[indB]*B) + 1 + n;
	return n;
}

double f (double net)
{
	return (1 / 1 + exp(-net));
}

double df (double net)
{
	return(f(net) * (1 - f(net)));
}

//Função de atualização do Peso
void ATTPeso (double peso[4], double pesoOut[2], int OutEsp,
		int Output, double netout, double nethid1,
		double nethid2, double h1, double h2, int A,
		int B)
{
	double delta;
	delta = (Output - OutEsp) * df(netout);

	pesoOut[1] = pesoOut[1] + (0.01 * delta * h1);
	pesoOut[2] = pesoOut[2] + (0.01 * delta * h2);

	delta = df(nethid1)*(delta*pesoOut[1]);

	peso[1] = peso[1] + (0.01 * delta * A);
	peso[3] = peso[3] + (0.01 * delta * B);

	delta = df(nethid2)*(delta*pesoOut[2]);

	peso[2] = peso[2] + (0.01 * delta * A);
	peso[4] = peso[4] + (0.01 * delta * B);
}

int main()
{
	//Estados iniciais
	int A[4], B[4], OutEsp[4];
	A[0] = 0; A[1] = 0; A[2] = 1; A[3] = 1;
	B[0] = 0; B[1] = 1; B[2] = 0; B[3] = 1;
	OutEsp[0] = 0; OutEsp[1] = 1; OutEsp[2] = 1; OutEsp[3] = 0;

	double h1, h2, out, nethid1, nethid2, netout, erro, Output[4], peso[4], pesoOut[2];
	peso[0] = 1; peso[1] = 1; peso[2] = 1; peso[3] = 1;
	pesoOut[0] = 1; pesoOut[1] = 1;
	erro = 1.0;

	//As interações estão descritas uma de cada vez por serem
	// apenas 3 neuronios e o erro não estar implementado ainda.

	while (erro > 0.01) {
		for(int i = 0; i < 4; i++)
		{
			nethid1 = net(peso, A[i], B[i], 1, 2);
			nethid2 = net(peso, A[i], B[i], 3, 4);
			netout = net(pesoOut, h1, h2, 1, 2);

			cout << " -- Inputs \nA = " << A[i] <<  "\nB = " << B[i] << "\n";

			h1 = f(nethid1);
			h2 = f(nethid2);
			out = f(netout);

			Output[i] = out;

			cout << "Output = " << Output[i] << "\n";

			erro = (Output[i] - OutEsp[i])*(Output[i] - OutEsp[i]);

			cout << "Erro: " << erro << "\n\n";

			ATTPeso (peso, pesoOut, OutEsp[i],
				Output[i], netout, nethid1, nethid2,
				h1, h2, A[i], B[i]);
		}
	}
}


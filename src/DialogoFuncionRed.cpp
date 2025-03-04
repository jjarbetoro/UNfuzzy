#include "DialogoFuncionRed.h"

DialogoFuncionRed::DialogoFuncionRed(red *r,wxWindow *parent)
:DialogoFuncion::DialogoFuncion(parent)
{
	Red=r;
	iniciar();
	//ctor
}

DialogoFuncionRed::~DialogoFuncionRed()
{
	//dtor
}

int DialogoFuncionRed::numeroEntradas()
{
	return Red->numeroEntradas();
}

int DialogoFuncionRed::numeroSalidas()
{
	return Red->numeroSalidas();
}

wxString DialogoFuncionRed::nombreEntrada(int i)
{
	wxString str=Red->variableEntrada(i)->nombreVariable();
	return str;
}

wxString DialogoFuncionRed::nombreSalida (int i)
{
	wxString str=Red->variableSalida(i)->nombreVariable();
	return str;
}

double DialogoFuncionRed::rangoMinimoEntrada(int i)
{
	return Red->variableEntrada(i)->rangoMinimo();
}

double DialogoFuncionRed::rangoMaximoEntrada(int i)
{
	return Red->variableEntrada(i)->rangoMaximo();
}

double DialogoFuncionRed::rangoMinimoSalida(int i)
{
	return Red->variableSalida(i)->rangoMinimo();
}

double DialogoFuncionRed::rangoMaximoSalida(int i)
{
	return Red->variableSalida(i)->rangoMaximo();
}


void DialogoFuncionRed::pintarFuncion(bool flagFondo, bool flagCurva, int numEntra,int numSale)
{
	wxClientDC dc(this);
	wxRect canvas=canvasFuncion->GetRect();
	Grafica = new Graficador(&dc,canvas);

	double mnx, mxx, mny, mxy;
	mnx=rangoMinimoEntrada(numEntra);
	mxx=rangoMaximoEntrada(numEntra);
	mny=rangoMinimoSalida(numSale);
	mxy=rangoMaximoSalida(numSale);
	wxString nomEntra=nombreEntrada(numEntra);
	wxString nomSale =nombreSalida (numSale);

	if(flagFondo)
	{
		Grafica->pintarFondoFuncion(mnx,mxx,mny,mxy,nomEntra,nomSale);
		long tam=entradasPintadas.Count();
		for(long j=0;j<tam;j++)
		{
			double entra[numeroEntradas()];
			for(int i=0;i<numeroEntradas();i++)
			{
				entra[i]=entradasPintadas[j][i];
			}
			Grafica->pintarCurvaFuncionES(Red, numEntra,numSale,entra,coloresPintados[j]);
		}
	}
	if(!flagCurva){return;}

	wxArrayDouble entradas;
	double entra[numeroEntradas()];
	for(int i=0;i<numeroEntradas();i++)
	{
		entra[i]=valoresEntradas[i]->GetValue();
		entradas.Add(entra[i]);
	}

	Grafica->pintarCurvaFuncionES(Red, numEntra,numSale,entra,colorData.GetColour());
	entradasPintadas.Add(entradas);
	coloresPintados.Add(colorData.GetColour());

}

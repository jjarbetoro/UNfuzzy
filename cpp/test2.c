// Código C del Sistema de Lógica Difusa

// Automatically generated by UNFUZZY V 3.0
// Author: Oscar Duarte (ogduartev@unal.edu.co)
// Universidad Nacional de Colombia
// Disclaimer: 
// The code generated is udes under the responsability of the user.
// It does not causes direct or indirect responsability neither for the author of UNFUZZY
// nor for Universidad Nacional de Colombia.
// 
// para compilar el archivo xxx.c:
//   g++ xxx.c

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

#define NUMEROREGLAS                 3
#define NUMEROVARIABLESENTRADA       1
#define NUMEROVARIABLESSALIDA        1
#define NUMEROTOTALCONJUNTOSENTRADA  3

struct conjunto{
	string nombre;
	float minimo;
	float maximo;
};

struct variable{
	string nombre;
	float minimo;
	float maximo;
	int intervalos;
	float intervalo;
	int numeroConjuntos;
};

struct difusor{
	float minimo;
	float maximo;
	float centro;
	float var1;
	float var2;
	float var3;
	float var4;
	int puntos;
	float intervalo;
};

struct variable VariablesEntrada[NUMEROVARIABLESENTRADA];
struct variable VariablesSalida[NUMEROVARIABLESSALIDA];
struct conjunto Entradas[NUMEROTOTALCONJUNTOSENTRADA];
struct difusor Difusores[NUMEROTOTALCONJUNTOSENTRADA];
int Reglas[NUMEROREGLAS][NUMEROVARIABLESENTRADA+NUMEROVARIABLESSALIDA];
float Modificadores[NUMEROREGLAS][NUMEROVARIABLESENTRADA];
float CentrosAltura[NUMEROREGLAS][NUMEROVARIABLESSALIDA];
void llenarDatos();
void llenarVariablesEntrada();
void llenarVariablesSalida();
void llenarEntradas();
void llenarDifusores();
void llenarReglas();
void llenarModificadores();
void llenarCentrosAltura();
void calcular(float *ent,float *sal);
float salidaConcreta(int NumeroSalida, float *entra);
float salidaConcreta0(float *entra);

float pertenenciaComposicion(int numVar, int numRegla, float sal);
float pertenenciaDifusores(float *ent);
float pertenenciaImplicacion(int numSal, int numRegla,float *ent, float sal);
float pertenenciaConsecuente(int numSal, int numRegla, float sal);
float pertenenciaAntecedente(int numRegla, float *ent);
int activarRegla(int numRegla);
float pertenenciaDifusor(int numVar, float x);
float pertenenciaVariableEntrada(int numVar,int numConj, float x);
float pertenenciaVariableSalida(int numVar,int numConj, float x);

int indiceEntradas(int numRegla,int numVar);
void actualizarEntradas(float *ent);
float Implicacion(float x,float y);
float Composicion(float x,float y);
float Conjuncion(float x,float y);
float And(float x,float y);

int main()
{
    float entra[NUMEROVARIABLESENTRADA];
    float sale[NUMEROVARIABLESSALIDA];
    char q='s';
    llenarDatos();
    while(q=='s')
    {
        int i;
        for(i=0;i<NUMEROVARIABLESENTRADA;i++)
        {
            float e;
            printf("%s : ",VariablesEntrada[i].nombre.c_str());
            scanf("%f",&e);
            entra[i]=e;
        }
        calcular(entra,sale);
        for(i=0;i<NUMEROVARIABLESSALIDA;i++)
        {
            printf("%s : ",VariablesSalida[i].nombre.c_str());
            printf("%f : \n",sale[i]);
        }
        printf("Do you want another calculus? (s/n)");
        fflush(stdin);
        scanf(" %c",&q);
    }
}
void llenarDatos()
{
    llenarVariablesEntrada();
    llenarVariablesSalida();
    llenarEntradas();
    llenarDifusores();
    llenarReglas();
    llenarModificadores();
    llenarCentrosAltura();
}
void calcular(float *entra, float *sale)
{
    int i;
    for(i=0;i<NUMEROVARIABLESSALIDA;i++)
    {
        sale[i]=salidaConcreta(i,entra);
    }
}
void actualizarEntradas(float *ent)
{
    float dx;
    int i;
    for(i=0;i<NUMEROVARIABLESENTRADA;i++)
    {
        dx=ent[i]-Difusores[i].centro;
        Difusores[i].centro=Difusores[i].centro+dx;
        Difusores[i].minimo=Difusores[i].minimo+dx;
        Difusores[i].maximo=Difusores[i].maximo+dx;
        Difusores[i].var1=Difusores[i].var1+dx;
        Difusores[i].var2=Difusores[i].var2+dx;
        Difusores[i].var3=Difusores[i].var3+dx;
        Difusores[i].var4=Difusores[i].var4+dx;
    }
}
int indiceEntradas(int numVar,int numConj)
{
    int contador=0;
    int i;
    for(i=0;i<numVar;i++)
    {
        contador=contador+VariablesEntrada[i].numeroConjuntos;
    }
    contador=contador+numConj;
    return contador;
}
float pertenenciaComposicion(int numVar,int numRegla, float sal)
{
    float ux;
    float uxa;
    float uxab;
    float comp=0;
    float x[NUMEROVARIABLESENTRADA];
    int inter[NUMEROVARIABLESENTRADA];
    if(!activarRegla(numRegla))
    {
        comp=Implicacion(0,0);
    }
    else{
        int casos=1;
        int i;
        for(i=0;i<NUMEROVARIABLESENTRADA;i++)
        {
            casos=casos*Difusores[i].puntos;
            inter[i]=1;
        }
        for(i=0;i<NUMEROVARIABLESENTRADA;i++)
        {
            int k;
            for(k=0;k<NUMEROVARIABLESENTRADA;k++)
            {
                x[k]=Difusores[k].minimo+Difusores[k].intervalo*inter[k];
                inter[k]=inter[k]+1;
                if(inter[k]>=Difusores[k].puntos)
                {
                    inter[k]=1;
                }
            }
            uxab=pertenenciaImplicacion(numVar,numRegla,x,sal);
            uxa=pertenenciaDifusores(x);
            ux=Composicion(uxa,uxab);
            if(ux>comp)
            {
                comp=ux;
            }
        }
    }
    return comp;
}
float pertenenciaDifusores(float *ent)
{
    float uxd;
    int j=0;
    uxd=pertenenciaDifusor(j,ent[j]);
    for(j=0;j<NUMEROVARIABLESENTRADA;j++)
    {
    uxd=And(uxd,pertenenciaDifusor(j,ent[j]));
    }
    return uxd;
}
float pertenenciaImplicacion(int numSal,int numRegla,float *ent,float sal)
{
    float uxa,uxb;
    uxa=pertenenciaAntecedente(numRegla,ent);
    uxb=pertenenciaConsecuente(numSal,numRegla,sal);
    return Implicacion(uxa,uxb);
}
float pertenenciaConsecuente(int numSal,int numRegla,float sal)
{
    float uxc;
    int conj;
    conj=Reglas[numRegla][NUMEROVARIABLESENTRADA+numSal];
    uxc=pertenenciaVariableSalida(numSal,conj,sal);
    return uxc;
}
float pertenenciaAntecedente(int numRegla,float *ent)
{
    float ux;
    float uxa;
    int conj;
    int j=0;
    conj=Reglas[numRegla][0];
    ux=pertenenciaVariableEntrada(j,conj,ent[j]);
    if(Modificadores[numRegla][0]>0.0)
    {
        uxa=pow(ux,Modificadores[numRegla][0]);
    }else
    {
        uxa=1;
    }
    for(j=1;j<NUMEROVARIABLESENTRADA;j++)
    {
        conj=Reglas[numRegla][j];
        ux=pertenenciaVariableEntrada(j,conj,ent[j]);
        if(Modificadores[numRegla][j]>0.0)
        {
            ux=pow(ux,Modificadores[numRegla][j]);
        }else
        {
            ux=1;
        }
        uxa=And(uxa,ux);
    }
    return uxa;
}
int activarRegla(int numRegla)
{
    int i;
    for(i=0;i<NUMEROVARIABLESENTRADA;i++)
    {
        float bmn,bmx,cmn,cmx;
        int numCon;
        int indice;
        numCon=Reglas[numRegla][i];
        indice=indiceEntradas(i,numCon);
        bmn=Entradas[indice].minimo;
        bmx=Entradas[indice].maximo;
        cmn=Difusores[i].minimo;
        cmx=Difusores[i].maximo;
        if(bmn>cmx||bmx<cmn)
            return 0;
    }
    return 1;
}
float salidaConcreta(int NumeroSalida,float *ent)
{
    float respuesta;
    switch(NumeroSalida)
    {
        case 0 : respuesta=salidaConcreta0(ent);break;
        default:respuesta=0;break;
    }
    return respuesta;
}
float salidaConcreta0(float *ent)
{
    int NumeroSalida=0;
    float con=0.000000;
    float y;
    float y1=0;
    float y2=0;
    float ymax;
    int i;
    int j;
    ymax=VariablesSalida[NumeroSalida].minimo;
    actualizarEntradas(ent);
    for(i=0;i<(VariablesSalida[NumeroSalida].intervalos+1);i++)
    {
        float con=0.000000;
        y=VariablesSalida[NumeroSalida].minimo+i*VariablesSalida[NumeroSalida].intervalo;
        for(j=0;j<NUMEROREGLAS;j++)
        {
            float temp;
            temp=pertenenciaComposicion(NumeroSalida,j,y);
            con=Conjuncion(con,temp);
        }
        y1=y1+y*con;
        y2=y2+con;
    }
    if(fabs(y2)<0.000001)
        y2=100000.0;
    if(fabs(y1)<0.000001)
        y1=0.0;
    ymax=y1/y2;
    return ymax;
}

void llenarVariablesEntrada()
{
    VariablesEntrada[0].nombre="Input 1";
    VariablesEntrada[0].minimo=-1.000000;
    VariablesEntrada[0].maximo=1.000000;
    VariablesEntrada[0].intervalos=20;
    VariablesEntrada[0].intervalo=0.100000;
    VariablesEntrada[0].numeroConjuntos=3;

}

void llenarVariablesSalida()
{
    VariablesSalida[0].nombre="Output 1";
    VariablesSalida[0].minimo=-1.000000;
    VariablesSalida[0].maximo=1.000000;
    VariablesSalida[0].intervalos=20;
    VariablesSalida[0].intervalo=0.100000;
    VariablesSalida[0].numeroConjuntos=3;

}
void llenarEntradas()
{
    Entradas[0].minimo=-1.000000;
    Entradas[0].maximo=0.000000;

    Entradas[1].minimo=-1.000000;
    Entradas[1].maximo=1.000000;

    Entradas[2].minimo=0.000000;
    Entradas[2].maximo=1.000000;

}
void llenarDifusores()
{
    Difusores[0].minimo=-0.005000;
    Difusores[0].maximo=0.005000;
    Difusores[0].centro=0.000000;
    Difusores[0].puntos=1;
    Difusores[0].intervalo=0.000000;
    Difusores[0].var1=-0.005000;
    Difusores[0].var2=0.005000;
    Difusores[0].var3=0.000000;
    Difusores[0].var4=0.000000;

}
void llenarReglas()
{
    Reglas[0][0]=0;
    Reglas[0][1]=0;

    Reglas[1][0]=1;
    Reglas[1][1]=1;

    Reglas[2][0]=2;
    Reglas[2][1]=2;

}

void llenarModificadores()
{
    Modificadores[0][0]=1.000000;
    Modificadores[1][0]=1.000000;
    Modificadores[2][0]=1.000000;
}
void llenarCentrosAltura()
{
    CentrosAltura[0][0]=-1.000000;
    CentrosAltura[1][0]=0.000000;
    CentrosAltura[2][0]=1.000000;
}

float pertenenciaDifusor(int numVar, float x)
{
    float ux=0;
    switch(numVar)
    {
        case 0:
            if(x<Difusores[0].var1)
            	ux=0;
            if(x<Difusores[0].var2&&x>=Difusores[0].var1)
            	ux=1;
            if(x>=Difusores[0].var2)
            	ux=0;
            break;
        default:break;
    }
    return ux;
}
float pertenenciaVariableEntrada(int numVar,int numConj, float x)
{
    float ux=0;
    switch(numVar)
    {
        case 0:
            switch(numConj)
            {
            case 0:
                        if(x<(-1.000000))
                            ux=1;
                        if(x<(-1.000000)&&x>=(-1.000000))
                            ux=1;
                        if(x<(0.000000)&&x>=(-1.000000))
                            ux=((0.000000)-x)/((0.000000)-(-1.000000));
                        if(x>=(0.000000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;
                break;
            case 1:
                        if(x<(-1.000000))
                            ux=0;
                        if(x<(0.000000)&&x>=(-1.000000))
                            ux=(x-(-1.000000))/((0.000000)-(-1.000000));
                        if(x<(1.000000)&&x>=(0.000000))
                            ux=((1.000000)-x)/((1.000000)-(0.000000));
                        if(x>=(1.000000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;

                break;
            case 2:
                        if(x<(0.000000))
                            ux=0;
                        if(x<(1.000000)&&x>=(0.000000))
                            ux=(x-(0.000000))/((1.000000)-(0.000000));
                        if(x>=(1.000000))
                            ux=1;
                        if(ux<0.0001)
                            ux=0;
                break;
            default:break;
            }break;
        default:break;
    }
    return ux;
}
float pertenenciaVariableSalida(int numVar,int numConj, float x)
{
    float ux=0;
    switch(numVar)
    {
        case 0:
            switch(numConj)
            {
            case 0:
                        if(x<(-1.000000))
                            ux=1;
                        if(x<(-1.000000)&&x>=(-1.000000))
                            ux=1;
                        if(x<(0.000000)&&x>=(-1.000000))
                            ux=((0.000000)-x)/((0.000000)-(-1.000000));
                        if(x>=(0.000000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;
                break;
            case 1:
                        if(x<(-1.000000))
                            ux=0;
                        if(x<(0.000000)&&x>=(-1.000000))
                            ux=(x-(-1.000000))/((0.000000)-(-1.000000));
                        if(x<(1.000000)&&x>=(0.000000))
                            ux=((1.000000)-x)/((1.000000)-(0.000000));
                        if(x>=(1.000000))
                            ux=0;
                        if(ux<0.0001)
                            ux=0;

                break;
            case 2:
                        if(x<(0.000000))
                            ux=0;
                        if(x<(1.000000)&&x>=(0.000000))
                            ux=(x-(0.000000))/((1.000000)-(0.000000));
                        if(x>=(1.000000))
                            ux=1;
                        if(ux<0.0001)
                            ux=0;
                break;
            default:break;
            }break;
        default:break;
    }
    return ux;
}
float Implicacion(float x,float y)
{
    float rel;
    if(x<y)
    {
    	rel=x;
    }else
    {
    	rel=y;
    }
    return rel;
}

float Composicion(float x,float y)
{
    float z;
    if(x<y)
    {
    	z=x;
    }else
    {
    	z=y;
    }
    return z;
}

float Conjuncion(float x,float y)
{
    float z;
    if(x>y)
    {
    	z=x;
    }else
    {
    	z=y;
    }
    return z;
}

float And(float x,float y)
{
    float z;
    if(x<y)
    {
    	z=x;
    }else
    {
    	z=y;
    }
    return z;
}


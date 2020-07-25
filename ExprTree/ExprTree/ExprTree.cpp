// ExprTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>

#include "Node.h"

// variables map (aka dictionary) stores correponding value given var name
std::map<std::string, int> variables;

int main()
{
    ConstNode A(1), B(2), C(3), D(4);
    VarNode X("x"), Y("y"), Z("z");
    variables["x"] = 100;
    variables["y"] = 200;
    variables["z"] = 300;

    // Naming Rules: a for Add, m for mutliply, d for derivate, s for sin
    AddNode AaB(&A, &B), AaC(&A, &C), CaD(&C, &D);
    AddNode AaX(&A, &X), CaY(&C, &Y), DaZ(&D, &Z);
    AddNode AaBaC(&AaB, &C), AaCaCaD(&AaC, &CaD);
    MutliplyNode AmB(&A, &B), AmC(&A, &C), CmD(&C, &D);
    MutliplyNode AmY(&A, &Y), BmY(&B, &Y), XmY(&X, &Y);
    MutliplyNode AmBmC(&AmB, &C), AmCmCmD(&AmC, &CmD);
    MutliplyNode AaBmC(&AaB, &C), AaCmCaD(&AaC, &CaD);
    MutliplyNode AaXmAmY(&AaX, &AmY), BmYmXmY(&BmY, &XmY);
    SinNode sAaBmC(&AaBmC);
    SinNode sAmY(&AmY), sXmY(&XmY);
    CosNode cAmY(&AmY), cBmYmXmY(&BmYmXmY);

    // use virtual function eval() to evaluate given Node (ExprTree)
    std::cout << A.eval() << std::endl;
    std::cout << B.eval() << std::endl;
    std::cout << C.eval() << std::endl;
    std::cout << D.eval() << std::endl;
    std::cout << X.eval() << std::endl;
    std::cout << Y.eval() << std::endl;
    std::cout << Z.eval() << std::endl;
    std::cout << AaB.eval() << std::endl;
    std::cout << AaC.eval() << std::endl;
    std::cout << CaD.eval() << std::endl;
    std::cout << AaX.eval() << std::endl;
    std::cout << AaBaC.eval() << std::endl;
    std::cout << AaCaCaD.eval() << std::endl;
    std::cout << AmB.eval() << std::endl;
    std::cout << AmC.eval() << std::endl;
    std::cout << CmD.eval() << std::endl;
    std::cout << AmY.eval() << std::endl;
    std::cout << AmBmC.eval() << std::endl;
    std::cout << AmCmCmD.eval() << std::endl;
    std::cout << AaBmC.eval() << std::endl;
    std::cout << AaCmCaD.eval() << std::endl;
    std::cout << sAaBmC.eval() << std::endl;

    std::cout << "Derivate:" << std::endl;
    /*
    std::cout << AmY.derivate("y")->eval() << std::endl;
    std::cout << BmY.derivate("y")->eval() << std::endl;
    std::cout << XmY.derivate("y")->eval() << std::endl;
    std::cout << XmY.derivate("x")->eval() << std::endl;
    std::cout << AaXmAmY.derivate("y")->eval() << std::endl;
    std::cout << AaXmAmY.derivate("x")->eval() << std::endl;
    std::cout << BmYmXmY.derivate("y")->eval() << std::endl;
    std::cout << BmYmXmY.derivate("x")->eval() << std::endl;
    std::cout << sAmY.derivate("y")->eval() << std::endl;
    std::cout << sXmY.derivate("y")->eval() << std::endl;
    std::cout << sXmY.derivate("x")->eval() << std::endl;
    std::cout << cAmY.derivate("y")->eval() << std::endl;
    std::cout << cAmY.derivate("x")->eval() << std::endl;
    std::cout << cBmYmXmY.derivate("y")->eval() << std::endl;
    std::cout << cBmYmXmY.derivate("x")->eval() << std::endl;
    */
    AmY.derivate("y")->toString(); std::cout << std::endl;
    BmY.derivate("y")->toString(); std::cout << std::endl;
    XmY.derivate("y")->toString(); std::cout << std::endl;
    XmY.derivate("x")->toString(); std::cout << std::endl;
    AaXmAmY.derivate("y")->toString(); std::cout << std::endl;
    AaXmAmY.derivate("x")->toString(); std::cout << std::endl;
    BmYmXmY.derivate("y")->toString(); std::cout << std::endl;
    BmYmXmY.derivate("x")->toString(); std::cout << std::endl;
    sAmY.derivate("y")->toString(); std::cout << std::endl;
    sXmY.derivate("y")->toString(); std::cout << std::endl;
    sXmY.derivate("x")->toString(); std::cout << std::endl;
    cAmY.derivate("y")->toString(); std::cout << std::endl;
    cAmY.derivate("x")->toString(); std::cout << std::endl;
    cBmYmXmY.derivate("y")->toString(); std::cout << std::endl;
    cBmYmXmY.derivate("x")->toString(); std::cout << std::endl;
}


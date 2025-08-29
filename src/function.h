#pragma once
bool isInBetween(int p, int q, double x); // To determine whether x is within the open interval (p, q)

bool isMouseInsideButton(int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight);
// To determine whether the mouse has clicked within the button area

bool isInsideGraph(double left, double right, double top, double bottom); // To determine whether something is within the graph

bool timer(int id, int duration);
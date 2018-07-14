#include "ledbar.h"

LedBar *ledBar;

void setup() { ledBar = new LedBar(); }

void loop() { ledBar->tick(); }
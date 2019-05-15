/* -*- C++ -*- */
#pragma once
/**
* @file menu.h
* @author Rui Azevedo
* @date 10 May 2019
* @copyright 2019 Rui Azevedo
* @brief use arduino standard LCD library as menu output
*/

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <menu.h>

//Output Device Operation
enum class OOP {RawOut,Measure};

template<LiquidCrystal& dev, typename O=FullPrinter<>>
struct LiquidCrystalOut:public O {
  using O::O;
  using This = LiquidCrystalOut<dev,O>;
  template<OOP op=OOP::RawOut>
  inline void nl() {O::useY();}
  template<typename T,OOP op=OOP::RawOut>
  inline void raw(T i) {
    // Serial<<"LCDOutDef::raw("<<i<<")"<<endl;
    // if (!O::operator bool()) return;//TODO: this is naive, we need to measure
    _trace(MDO<<"{0}");
    if (This::posY()<0) return;//O::useX(O::measure(i));//we only need to measure lines!
    _trace(MDO<<"{1}");
    if (This::posY()>This::height()) return;
    _trace(MDO<<"{2}");
    dev.setCursor(O::posX(),O::posY());
    Serial<<"lcd.setCursor("<<O::posX()<<","<<O::posY()<<") "<<i<<endl;
    if (op==OOP::RawOut) O::useX(dev.print(i));
    else O::useX(O::measure(i));
  }
  inline void clear() {
    O::newView();
    dev.clear();
  }
  // template<typename H>
  // inline void clearLine(PrintHead<H> p) {
  //   int line=p.line;//O::posY();
  //   // Serial<<"LCDOutDef::clearLine "<<p.pos<<(O::scrlPosY()>=0?"+":"")<<O::scrlPosY()<<"="<<line<<endl;
  //   // Serial<<"height:"<<p.printer.height()<<endl;
  //   if (line<0||line>=p.printer.height()) return;
  //   // Serial<<"LCDOutDef::clearLine "<<line<<endl;
  //   dev.setCursor(0,line);
  //   for(int n=0;n<p.printer.width();n++)
  //     dev.print(" ");
  // }
};

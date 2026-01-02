#include "EmitterLib.h"
#include <iostream>
#include <string>
#include <memory>

class Monitor : public Listener<std::string> {

  public:
  

  Monitor()
    : counter{0} {};

  void onEvent(const std::string& recieved) override {
    std::cout << "i recieved: " << recieved << std::endl;
    ++counter;
    }

  int getCounter() {
    return counter; 
  }
  
  
  private:

  int counter;
  
};

int main(void)
{

  Emitter<std::string> textEmitter;
  auto monitor = std::make_shared<Monitor>();

  auto textMonitorId = textEmitter.subscribe(monitor);

  
  int c = monitor->getCounter();

  std::cout << c << std::endl;
  textEmitter.emit("hello world!");

  c = monitor->getCounter(); 
  std::cout << c << std::endl;

  textEmitter.unsubscribe(textMonitorId);
  textEmitter.emit("i like trains");

  textMonitorId = textEmitter.subscribe(monitor);
  textEmitter.emit("i like trains");
  c = monitor->getCounter(); 
  std::cout << c << std::endl;
  
  return 0; 
}

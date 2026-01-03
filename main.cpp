#include "EmitterLib.h"
#include <iostream>
#include <string>
#include <memory>

class Monitor : public Listener<std::string> {

  public:
  

  Monitor()
    : counter{0} {};
  Monitor(int init_c)
    : counter{init_c} {};
    
  void onEvent(const std::string& recieved) override {
    std::cout << "my counter is: " << counter << " I recieved: " << recieved << std::endl;
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
  auto monitor2 = std::make_shared<Monitor>(10);
  
  auto textMonitorId = textEmitter.subscribe(monitor);
  auto monitor2Id = textEmitter.subscribe(monitor2);
  
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

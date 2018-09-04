class Visor {

  // Parameters of the class
  PVector pos, size, orig_size, rect_selected_pos, rect_selected_size;
  PImage frame;
  
  // Constructor of the class
  Visor(PVector pos_, PVector size_) {
  
    pos = pos_.copy();
    size = size_.copy();
  
  }

  // Class' methods
  
  void update() {}
  
  void display() {}
  
}

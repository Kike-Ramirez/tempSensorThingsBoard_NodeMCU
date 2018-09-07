class Visor {

  // Parameters of the class
  PVector pos, size, orig_size, max_size, rect_selected_pos, rect_selected_size;
  PImage frame;
  PGraphics canvas;
  Movie movie;
  
  // Constructor of the class
  Visor(PGraphics canvas_, Movie mov_, PVector pos_, PVector size_) {
  
    pos = pos_.copy();
    size = size_.copy();
    max_size = new PVector(640, 480);
    rect_selected_pos = new PVector(0,0);
    rect_selected_size = new PVector(128, 64);
    canvas = canvas_;
    movie = mov_;
    
  }

  // Class' methods
  
  void update() {
  
  }
  
  void display() {
  
  }
  
}

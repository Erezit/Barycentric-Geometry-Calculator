#include "toolsMode.h"

#include <ginac/ginac.h>

#include <cmath>
float max(float num1, float num2) {
  if (num1 > num2) {
    return num1;
  }
  return num2;
}

int counter = 0;
void ChangeColorToActive(std::vector<Shape*> objects) {
  if (objects.size() != counter) {
    if (objects.size() == 0) {
      counter = 0;
      return;
    }
    dynamic_cast<Shape*>(objects[objects.size() - 1])->choosenActive();
    ++counter;
  }
}

void ChangeColorToFinal(std::vector<Shape*> objects) {
  counter = 0;
  for (auto obj : objects) {
    obj->choosenFinal();
  }
}

void MoveBasePoint::active(Scene& cur_scene) {
  sf::Event& cur_event = cur_scene.event;
  if (cur_event.type == sf::Event::MouseButtonReleased) {
    is_moving = false;
    last_object = nullptr;
  }
  if (cur_event.type == sf::Event::MouseButtonPressed &&
      cur_event.type != sf::Event::MouseButtonReleased) {
    is_moving = true;
  }

  if (is_moving) {
    Shape* movable_object = cur_scene.selectObject<Point>();
    if (movable_object != nullptr && last_object == nullptr) {
      last_object = movable_object;
    }

    if (last_object != nullptr) {
      movable_object = last_object;
    }

    if (Point* movable_point = dynamic_cast<BasePoint*>(movable_object)) {
      movable_point->circle.setPosition(global::window.mapPixelToCoords(
          sf::Mouse::getPosition(global::window)));
      movable_point->x_coord_ =
          max(110, global::window
                       .mapPixelToCoords(sf::Mouse::getPosition(global::window))
                       .x);
      movable_point->y_coord_ =
          global::window
              .mapPixelToCoords(sf::Mouse::getPosition(global::window))
              .y;
    }
  }
}

bool MoveBasePoint::is_moving = false;

Shape* MoveBasePoint::last_object = nullptr;

void CreateMiddlePoint::active(Scene& current_scene) {
  // std::cout << current_scene.selected_shapes.size() << std::endl;
  current_scene.TryGetObject<Point>();
  ChangeColorToActive(current_scene.selected_shapes);
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(2)) {
    Point* first_point = dynamic_cast<Point*>(current_scene.selected_shapes[0]);
    Point* second_point =
        dynamic_cast<Point*>(current_scene.selected_shapes[1]);
    std::cout << std::endl <<  "Generating the midpoint between points " << (first_point -> name.getName()).getString().toAnsiString() << " and " << (second_point -> name.getName()).getString().toAnsiString() <<  std::endl << std::endl;
    MiddlePoint* middlePoint = new MiddlePoint(first_point, second_point);
    current_scene.objects.push_back(middlePoint);
    ChangeColorToFinal(current_scene.selected_shapes);
    current_scene.selected_shapes.clear();
  }
}

void CreateLine::active(Scene& current_scene) {
  current_scene.TryGetObject<Point>();
  ChangeColorToActive(current_scene.selected_shapes);
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(2)) {
    Point* first_point = dynamic_cast<Point*>(current_scene.selected_shapes[0]);
    Point* second_point =
        dynamic_cast<Point*>(current_scene.selected_shapes[1]);
    std::cout << std::endl <<  "Generating the line  between points " << (first_point -> name.getName()).getString().toAnsiString() << " and " << (second_point -> name.getName()).getString().toAnsiString() <<  std::endl << std::endl;
    Line* line = new Line(first_point, second_point);
    current_scene.objects.push_back(line);
    ChangeColorToFinal(current_scene.selected_shapes);
    current_scene.selected_shapes.clear();
  }
}

void FindLineIntersection::active(Scene& current_scene) {
  current_scene.TryGetObject<Line>();
  ChangeColorToActive(current_scene.selected_shapes);
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(0, 2)) {
    std::cout << std::endl << "Generating the intersection point!" << std::endl;
    Line* first_line = dynamic_cast<Line*>(current_scene.selected_shapes[0]);
    Line* second_line = dynamic_cast<Line*>(current_scene.selected_shapes[1]);
    PointByTwoLines* point = new PointByTwoLines(first_line, second_line);
    current_scene.objects.push_back(point);
    ChangeColorToFinal(current_scene.selected_shapes);
    current_scene.selected_shapes.clear();
  }
}

bool RollBack::flag = true;

void RollBack::active(Scene& current_scene) {
  sf::Event& cur_event = current_scene.event;
  if (cur_event.type == sf::Event::MouseButtonPressed && !flag) {
    flag = true;
  }
  if (cur_event.type == sf::Event::MouseButtonReleased && flag) {
    if (current_scene.objects.size() > 6) {
      current_scene.objects.pop_back();
    }
    flag = false;
  }
}

bool MoveName::is_moving = false;
Shape* MoveName::last_object = nullptr;

void MoveName::active(Scene& current_scene) {
  sf::Event& cur_event = current_scene.event;
  if (cur_event.type == sf::Event::MouseButtonReleased) {
    is_moving = false;
    last_object = nullptr;
  }
  if (cur_event.type == sf::Event::MouseButtonPressed &&
      cur_event.type != sf::Event::MouseButtonReleased) {
    is_moving = true;
  }
  if (is_moving) {
    Shape* movable_object = current_scene.selectObject<Point>();
    if (movable_object != nullptr && last_object == nullptr) {
      last_object = movable_object;
    }

    if (last_object != nullptr) {
      movable_object = last_object;
    }

    if (Point* movable_point = dynamic_cast<Point*>(movable_object)) {
      sf::Vector2f point_position =
          sf::Vector2f(movable_point->x_coord_, movable_point->y_coord_);
      sf::Vector2f mouse_position = global::window.mapPixelToCoords(
          sf::Mouse::getPosition(global::window));
      sf::Vector2f new_delta = mouse_position - point_position;
      double size = sqrt(new_delta.x * new_delta.x + new_delta.y * new_delta.y);
      new_delta.x = new_delta.x / size * 15;
      new_delta.y = new_delta.y / size * 15;
      movable_point->name.setDelta(new_delta);
    }
  }
}

void ShowBarycentricCoordinate::active(Scene& current_scene) {
  current_scene.TryGetObject<Point>();
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(1)) {
      Point* first_point = dynamic_cast<Point*>(current_scene.selected_shapes[0]);
      std::cout << std::endl <<  "Barycentric coordinates point " << (first_point -> name.getName()).getString().toAnsiString()  <<  std::endl << std::endl;
    std::cout
        << "Relative to the vertex A: " <<  current_scene.selected_shapes[0]->getCoordinates().getACoordinate()
        << std::endl
        << "Relative to the vertex B: " << current_scene.selected_shapes[0]->getCoordinates().getBCoordinate() << std::endl
        << "Relative to the vertex C: " <<current_scene.selected_shapes[0]->getCoordinates().getCCoordinate()
        << std::endl;
    std::cout << "Or in another form: " << std::endl;
        std::cout
        << "Relative to the vertex A: " << "(" << factor(first_point -> getCoordinates().getACoordinate().numer()) << ")" << " / " << "(" << factor(first_point -> getCoordinates().getACoordinate().denom()) << ")"
        << std::endl
        << "Relative to the vertex B: " <<  "(" << factor(first_point -> getCoordinates().getBCoordinate().numer()) << ")" << " / " << "(" << factor(first_point -> getCoordinates().getBCoordinate().denom()) << ")" << std::endl
        << "Relative to the vertex C: " <<  "(" << factor(first_point -> getCoordinates().getCCoordinate().numer()) << ")" << " / " << "(" << factor(first_point -> getCoordinates().getCCoordinate().denom()) << ")" << std::endl << std::endl;
      current_scene.selected_shapes.clear();
  }
}

template <typename T>
T Det(const T& A1, const T& B1, const T& C1, const T& A2, const T& B2,
      const T& C2, const T& A3, const T& B3, const T& C3) {
  return B1 * C2 * A3 - B2 * C1 * A3 + A2 * C1 * B3 - A1 * C2 * B3 +
         A1 * B2 * C3 - B1 * A2 * C3;
}

void ProveIntersect::active(Scene& current_scene) {
  current_scene.TryGetObject<Line>();
  ChangeColorToActive(current_scene.selected_shapes);
  if ((current_scene.event.type == sf::Event::MouseButtonReleased || global::fake_click) &&
      current_scene.Checker(0, 3)) {
    BarycentricCoordinates line_a_coordinate =
        current_scene.selected_shapes[0]->getCoordinates();
    BarycentricCoordinates line_b_coordinate =
        current_scene.selected_shapes[1]->getCoordinates();
    BarycentricCoordinates line_c_coordinate =
        current_scene.selected_shapes[2]->getCoordinates();
    GiNaC::ex det = Det<GiNaC::ex>(
        line_a_coordinate.getACoordinate(), line_a_coordinate.getBCoordinate(),
        line_a_coordinate.getCCoordinate(), line_b_coordinate.getACoordinate(),
        line_b_coordinate.getBCoordinate(), line_b_coordinate.getCCoordinate(),
        line_c_coordinate.getACoordinate(), line_c_coordinate.getBCoordinate(),
        line_c_coordinate.getCCoordinate());
    std::cout << std::endl;
    if (det.numer().normal() == 0) {
       std::cout << "The problem is solved, the selected lines are intersect in one point" << std::endl;
       std::cout << "The final determinant:" << std::endl;
       std::cout << det << std::endl;
       global::is_problem_correct = true; // for testing

    } else {
       std::cout << "The problem is incorrect" << std::endl;
       std::cout << "But the task can be true under the following conditions:" << std::endl;
       std::cout << factor(det.normal().numer()) << " = 0" << std::endl << std::endl;
       global::is_problem_correct = false; // for testing
    }
    ChangeColorToFinal(current_scene.selected_shapes);
    current_scene.selected_shapes.clear();
  }
}

void ProveCollinearity::active(Scene& current_scene) {
  current_scene.TryGetObject<Point>();
  ChangeColorToActive(current_scene.selected_shapes);
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(3)) {
    BarycentricCoordinates point_a_coordinate =
        current_scene.selected_shapes[0]->getCoordinates();
    BarycentricCoordinates point_b_coordinate =
        current_scene.selected_shapes[1]->getCoordinates();
    BarycentricCoordinates point_c_coordinate =
        current_scene.selected_shapes[2]->getCoordinates();
    GiNaC::ex det = Det<GiNaC::ex>(point_a_coordinate.getACoordinate(),
                                   point_a_coordinate.getBCoordinate(),
                                   point_a_coordinate.getCCoordinate(),
                                   point_b_coordinate.getACoordinate(),
                                   point_b_coordinate.getBCoordinate(),
                                   point_b_coordinate.getCCoordinate(),
                                   point_c_coordinate.getACoordinate(),
                                   point_c_coordinate.getBCoordinate(),
                                   point_c_coordinate.getCCoordinate());
    std::cout << std::endl;
    if (det.numer().normal() == 0) {
      std::cout << "The problem is solved, the selected points are collinear" << std::endl;
      std::cout << "The final determinant:" << std::endl;
      std::cout << det << std::endl;
    } else {
       std::cout << "The problem is incorrect" << std::endl;
       std::cout << "But the task can be true under the following conditions:" << std::endl;
       std::cout << factor(det.normal().numer()) << " = 0" << std::endl << std::endl;
    }
    ChangeColorToFinal(current_scene.selected_shapes);
    current_scene.selected_shapes.clear();
  }
}

bool DrawIncenter::single = false;

void DrawIncenter::active(Scene& current_scene) {
  sf::Event& cur_event = current_scene.event;
  if (cur_event.type == sf::Event::MouseButtonReleased && !single) {
    single = true;
    current_scene.objects.push_back(
        new Incenter(dynamic_cast<Point*>(current_scene.objects[0]),
                     dynamic_cast<Point*>(current_scene.objects[1]),
                     dynamic_cast<Point*>(current_scene.objects[2])));
  }
}

bool drawOrthocenter::single = false;

void drawOrthocenter::active(Scene& current_scene) {
  sf::Event& cur_event = current_scene.event;
  if (cur_event.type == sf::Event::MouseButtonReleased && !single) {
    single = true;
    current_scene.objects.push_back(
        new Orthocenter(dynamic_cast<Point*>(current_scene.objects[0]),
                        dynamic_cast<Point*>(current_scene.objects[1]),
                        dynamic_cast<Point*>(current_scene.objects[2])));
  }
}


extern GiNaC::symbol a;
extern GiNaC::symbol b;
extern GiNaC::symbol c;

void ProvePendicular::active(Scene& current_scene) {
  current_scene.TryGetObject<Line>();
  ChangeColorToActive(current_scene.selected_shapes);
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(0, 2)) {
    Line* line_a = dynamic_cast<Line*>(current_scene.selected_shapes[0]);
    Line* line_b = dynamic_cast<Line*>(current_scene.selected_shapes[1]);
    VectorDiff vector_diff_line_a;
    BarycentricCoordinates tmp_a_bar_coord = line_a -> getCoordinates();
    VectorDiff vector_diff_line_b;
    BarycentricCoordinates tmp_b_bar_coord = line_b -> getCoordinates();
    GiNaC::ex A1 = tmp_a_bar_coord.getBCoordinate() - tmp_a_bar_coord.getCCoordinate();
    GiNaC::ex B1 = tmp_a_bar_coord.getCCoordinate() - tmp_a_bar_coord.getACoordinate();
    GiNaC::ex C1 = tmp_a_bar_coord.getACoordinate() - tmp_a_bar_coord.getBCoordinate();
    GiNaC::ex A2 = tmp_b_bar_coord.getBCoordinate() - tmp_b_bar_coord.getCCoordinate();
    GiNaC::ex B2 = tmp_b_bar_coord.getCCoordinate() - tmp_b_bar_coord.getACoordinate();
    GiNaC::ex C2 = tmp_b_bar_coord.getACoordinate() - tmp_b_bar_coord.getBCoordinate();

    GiNaC::ex diff = (c * c + b * b - a * a) * (B1 + C1) * (B2 + C2) + (c * c - b * b + a * a) * (A1 + C1) * (A2 + C2) + (-c * c + b * b + a * a) * (B1 + A1) * (B2 + A2);
      std::cout << std::endl;
    if (diff.normal() == 0) {
      std::cout << "The problem is solved, the selected lines are perpendicular" << std::endl;
      std::cout << "The final determinant:" << std::endl;
      std::cout << diff << std::endl << std::endl;
    } else {
      std::cout << "The problem is incorrect" << std::endl;
      std::cout << "But the task can be true under the following conditions:" << std::endl;
      std::cout << factor(diff.normal().numer()) << " = 0" << std::endl << std::endl;
    }
    ChangeColorToFinal(current_scene.selected_shapes);
    current_scene.selected_shapes.clear();
  }
}

void FindDistance::active(Scene& current_scene) {
  current_scene.TryGetObject<Point>();
  ChangeColorToActive(current_scene.selected_shapes);
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(2)) {
    Point* first_point = dynamic_cast<Point*>(current_scene.selected_shapes[0]);
    Point* second_point =
        dynamic_cast<Point*>(current_scene.selected_shapes[1]);
    VectorDiff vector_diff(first_point, second_point);
    GiNaC::ex distance = -a * a * (vector_diff.B() * vector_diff.C()) -
                         b * b * (vector_diff.A() * vector_diff.C()) -
                         c * c * (vector_diff.B() * vector_diff.A());
    std::cout << std::endl;
    std::cout << "The distance between the points " << (first_point -> name.getName()).getString().toAnsiString() << " and " << (second_point -> name.getName()).getString().toAnsiString() << " equals: " << std::endl;
    ChangeColorToFinal(current_scene.selected_shapes);
    distance = distance.normal();
    std::cout << distance << std::endl;
    std::cout << "Or in another form" << std::endl;
    std::cout << "(" << factor(distance.numer().normal())<<")" << " / " << "(" << factor(distance.denom().normal()) << ")" << std::endl << std::endl;
    
    current_scene.selected_shapes.clear();
  }
}

void FindIsogonal::active(Scene& current_scene) {
  current_scene.TryGetObject<Point>();
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(1)) {
    Point* isogonal_point = new IsogonalPoint(
        dynamic_cast<Point*>(current_scene.objects[0]),
        dynamic_cast<Point*>(current_scene.objects[1]),
        dynamic_cast<Point*>(current_scene.objects[2]),
        dynamic_cast<Point*>(current_scene.selected_shapes[0]));
    std::cout << "Generating a isogonal point by point "  << (isogonal_point -> name.getName()).getString().toAnsiString() << std::endl;
    current_scene.objects.push_back(isogonal_point);
    current_scene.selected_shapes.clear();
  }
}

void CreateCircleByPoints::active(Scene& current_scene) {
  current_scene.TryGetObject<Point>();
  ChangeColorToActive(current_scene.selected_shapes);
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(3)) {
    Point* first_point = dynamic_cast<Point*>(current_scene.selected_shapes[0]);
    Point* second_point =
        dynamic_cast<Point*>(current_scene.selected_shapes[1]);
    Point* third_point = dynamic_cast<Point*>(current_scene.selected_shapes[2]);
    std::cout << "Generating a circle by points " << (first_point -> name.getName()).getString().toAnsiString() << " " <<  (second_point -> name.getName()).getString().toAnsiString() << " " << (third_point -> name.getName()).getString().toAnsiString()  << std::endl;
    Circle* circle = new Circle(first_point, second_point, third_point);
    current_scene.objects.push_back(circle);
    ChangeColorToFinal(current_scene.selected_shapes);
    current_scene.selected_shapes.clear();
  }
}


void MakeHidden::active(Scene& current_scene) {
  current_scene.TryGetObject<Point>();
  if (current_scene.event.type == sf::Event::MouseButtonReleased &&
      current_scene.Checker(1)) {
    Point* first_point = dynamic_cast<Point*>(current_scene.selected_shapes[0]);
    first_point -> changeHidden();
    current_scene.selected_shapes.clear();  
  }
}

void FindIntersectionByLineCircle::active(Scene& current_scene) {
  if(current_scene.selected_shapes.size() < 2) {
    current_scene.TryGetObject<>();
  } else {
    current_scene.TryGetObject<Point>();
  }
  ChangeColorToActive(current_scene.selected_shapes);
  if (current_scene.event.type == sf::Event::MouseButtonReleased && current_scene.Checker(1, 1, 1)) {
    std::cout << "Try to make a new intersection point by Line and Circle" << std::endl;
    Circle* circle = dynamic_cast<Circle*>(current_scene.selected_shapes[0]);
    Line* line = dynamic_cast<Line*>(current_scene.selected_shapes[1]);
    Point* point = dynamic_cast<Point*>(current_scene.selected_shapes[2]);
    if(circle && line && point) {
      std::cout << "Generating the intersection point by Line and Circle" << std::endl;
      Point* new_point = new PointIntersectionByLineCircle(circle, line, point);
      current_scene.objects.push_back(new_point);
    } else {
      std::cout << "Wrong order!" << std::endl;
      std::cout << "First you have to choose a circle, then a straight line and then a point" << std::endl;
    }
    ChangeColorToFinal(current_scene.selected_shapes);
    current_scene.selected_shapes.clear();
  }
}

void ProofTangencyCircles::active(Scene& current_scene) {
    current_scene.TryGetObject<Circle>();
    ChangeColorToActive(current_scene.selected_shapes);
    if (current_scene.event.type == sf::Event::MouseButtonReleased && current_scene.Checker(0, 0, 2)) {
      Circle* circle1 = dynamic_cast<Circle*>(current_scene.selected_shapes[0]);
      Circle* circle2 = dynamic_cast<Circle*>(current_scene.selected_shapes[1]);
       
      BarycentricCoordinates circle_coordinate1 = circle1 -> getCoordinates();
      BarycentricCoordinates circle_coordinate2 = circle2 -> getCoordinates();

      BarycentricCoordinates line_coordinate;
      GiNaC::ex sum1 = circle_coordinate1.findSum();
      GiNaC::ex sum2 = circle_coordinate2.findSum();

      line_coordinate.setCoordinates(circle_coordinate1.getACoordinate() / sum1 - circle_coordinate2.getACoordinate() / sum2, circle_coordinate1.getBCoordinate() / sum1 - circle_coordinate2.getBCoordinate() / sum2, circle_coordinate1.getCCoordinate() / sum1 - circle_coordinate2.getCCoordinate() / sum2);
      GiNaC::ex Da = line_coordinate.getBCoordinate() -line_coordinate.getCCoordinate();
      GiNaC::ex Db = line_coordinate.getCCoordinate() -line_coordinate.getACoordinate();
      GiNaC::ex Dc = line_coordinate.getACoordinate() -line_coordinate.getBCoordinate();
      GiNaC::ex X0 = 0;
      GiNaC::ex Y0 = line_coordinate.getCCoordinate();
      GiNaC::ex Z0 = -line_coordinate.getBCoordinate();
      GiNaC::ex det = a * a * Db * Dc + b * b * Dc * Da + c * c * Da * Db;
      GiNaC::ex det_a = -a * a * (Db * Z0 + Dc * Y0);
      GiNaC::ex det_b = -b * b * (Dc * X0 + Da * Z0);
      GiNaC::ex det_c = -c * c * (Da * Y0 + Db * X0);
      GiNaC::ex det_more = (X0 + Y0 + Z0) * (circle_coordinate1.getACoordinate() * Da + circle_coordinate1.getBCoordinate() * Db + circle_coordinate1.getCCoordinate() * Dc);
      GiNaC::ex last_a = -a * a * Y0 * Z0;
      GiNaC::ex last_b = -b * b * X0 * Z0;
      GiNaC::ex last_c = -c * c * Y0 * X0;
      GiNaC::ex last = (X0 + Y0 + Z0) * (circle_coordinate1.getACoordinate() * Z0 + circle_coordinate1.getBCoordinate() * Y0 + circle_coordinate1.getCCoordinate() * Z0);
      GiNaC::ex C_pol = last_a + last_b + last_c + last;
      GiNaC::ex B_pol = -det; 
      GiNaC::ex A_pol = det_more + det_a + det_b + det_c;
      GiNaC::ex D_pol = B_pol * B_pol - 4 * A_pol * C_pol;
      std::cout << D_pol << std::endl;
      std::cout << "In this version, the method does not work correctly" << std::endl;
      if(D_pol.normal() == 0) {
        std::cout << "YES" << std::endl;
      } else {
        std::cout << "NO" << std::endl;
      }
      ChangeColorToFinal(current_scene.selected_shapes);
      current_scene.selected_shapes.clear();
    }
}

void FindPerpendicularLine::active(Scene& current_scene) {
  if(current_scene.selected_shapes.size() < 1) {
    current_scene.TryGetObject<Line>();
  } else {
    current_scene.TryGetObject<Point>();
  }
  ChangeColorToActive(current_scene.selected_shapes);
  if (current_scene.event.type == sf::Event::MouseButtonReleased && current_scene.Checker(1, 1, 0)) {
    std::cout << "Try to make a new perpendicular Line" << std::endl;
    Line* line = dynamic_cast<Line*>(current_scene.selected_shapes[0]);
    Point* point = dynamic_cast<Point*>(current_scene.selected_shapes[1]);
    if(line && point) {
      std::cout << "Generating a perpendicular Line" << std::endl;
      PerpendicularLine* new_line = new PerpendicularLine(line, point);
      current_scene.objects.push_back(new_line);
    } else {
      std::cout << "Wrong order!" << std::endl;
      std::cout << "First you have to choose a straight line and then a point" << std::endl;
    }
   ChangeColorToFinal(current_scene.selected_shapes);
   current_scene.selected_shapes.clear();
  }
}


void FindParallelLine::active(Scene& current_scene) {
  if(current_scene.selected_shapes.size() < 1) { 
     current_scene.TryGetObject<Line>();
   } else { 
     current_scene.TryGetObject<Point>();
   } 
   ChangeColorToActive(current_scene.selected_shapes);
   if (current_scene.event.type == sf::Event::MouseButtonReleased && current_scene.Checker(1, 1, 0)) { 
   std::cout << "Try to make a new paralle Line" << std::endl;
   Line* line = dynamic_cast<Line*>(current_scene.selected_shapes[0]);
   Point* point = dynamic_cast<Point*>(current_scene.selected_shapes[1]);
   if(line && point) { 
     std::cout << "Generating a paralle Line" << std::endl;
     ParallelLine* new_line = new ParallelLine(line, point);
     current_scene.objects.push_back(new_line);
   } else {
     std::cout << "Wrong order!" << std::endl;
     std::cout << "First you have to choose a straight line and then a point" << std::endl;
   }
   ChangeColorToFinal(current_scene.selected_shapes);
   current_scene.selected_shapes.clear();
   }
}

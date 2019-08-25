void PrintVector(std::vector<int> v) {
  std::cout << "{ ";
  for (auto item : v) {
    std::cout << item << " ";
  }
  std::cout << "}" << "\n";
}

void PrintVectorOfVectors(std::vector<std::vector<int>> v) {
  for (auto row : v) {
    std::cout << "{ ";
    for (auto col : row) {
      std::cout << col << " ";
    }
    std::cout << "}" << "\n";
  }
}

void PrintVectorOfVectors(std::vector<std::vector<State>> v) {
  for (auto row : v) {
    std::cout << "{ ";
    for (auto col : row) {
      std::cout << CellString(col) << " ";
    }
    std::cout << "}" << "\n";
  }
}

void TestHeuristic() {
  std::cout << "----------------------------------------------------------" << "\n";
  std::cout << "Heuristic Function Test: ";
  if (Heuristic(1, 2, 3, 4) != 4) {
    std::cout << "failed" << "\n";
    std::cout << "\n" << "Heuristic(1, 2, 3, 4) = " << Heuristic(1, 2, 3, 4) << "\n";
    std::cout << "Correct result: 4" << "\n";
    std::cout << "\n";
  } else if (Heuristic(2, -1, 4, -7) != 8) {
    std::cout << "TestHeuristic Failed" << "\n";
    std::cout << "\n" << "Heuristic(2, -1, 4, -7) = " << Heuristic(2, -1, 4, -7) << "\n";
    std::cout << "Correct result: 8" << "\n";
    std::cout << "\n";
  } else {
    std::cout << "passed" << "\n";
  }
  std::cout << "----------------------------------------------------------" << "\n";
}

void TestAddToOpen() {
  std::cout << "----------------------------------------------------------" << "\n";
  std::cout << "AddToOpen Function Test: ";
  int x = 3;
  int y = 0;
  int g = 5;
  int h = 7;
  std::vector<std::vector<int>> open{{0, 0, 2, 9}, {1, 0, 2, 2}, {2, 0, 2, 4}};
  std::vector<std::vector<int>> solution_open = open; 
  solution_open.push_back(std::vector<int>{3, 0, 5, 7});
  std::vector<std::vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty, State::kObstacle, State::kEmpty}};
  std::vector<std::vector<State>> solution_grid = grid;
  solution_grid[3][0] = State::kClosed;
  AddToOpen(x, y, g, h, open, grid);
  if (open != solution_open) {
    std::cout << "failed" << "\n";
    std::cout << "\n";
    std::cout << "Your open list is: " << "\n";
    PrintVectorOfVectors(open);
    std::cout << "Solution open list is: " << "\n";
    PrintVectorOfVectors(solution_open);
    std::cout << "\n";
  } else if (grid != solution_grid) {
    std::cout << "failed" << "\n";
    std::cout << "\n";
    std::cout << "Your grid is: " << "\n";
    PrintVectorOfVectors(grid);
    std::cout << "\n";
    std::cout << "Solution grid is: " << "\n";
    PrintVectorOfVectors(solution_grid);
    std::cout << "\n";
  } else {
    std::cout << "passed" << "\n";
  }
  return;
}

void TestCompare() {
  std::cout << "----------------------------------------------------------" << "\n";
  std::cout << "Compare Function Test: ";
  std::vector<int> test_1 {1, 2, 5, 6};
  std::vector<int> test_2 {1, 3, 5, 7};
  std::vector<int> test_3 {1, 2, 5, 8};
  std::vector<int> test_4 {1, 3, 5, 7};
  if (Compare(test_1, test_2)) {
    std::cout << "failed" << "\n";
    std::cout << "\n" << "a = ";
    PrintVector(test_1);
    std::cout << "b = ";
    PrintVector(test_2);
    std::cout << "Compare(a, b): " << Compare(test_1, test_2) << "\n";
    std::cout << "Correct answer: 0" << "\n";
    std::cout << "\n";
  } else if (!Compare(test_3, test_4)) {
    std::cout << "failed" << "\n";
    std::cout << "\n" << "a = ";
    PrintVector(test_3);
    std::cout << "b = ";
    PrintVector(test_4);
    std::cout << "Compare(a, b): " << Compare(test_3, test_4) << "\n";
    std::cout << "Correct answer: 1" << "\n";
    std::cout << "\n";
  } else {
    std::cout << "passed" << "\n";
  }
  return;
}

void TestSearch() {
  std::cout << "----------------------------------------------------------" << "\n";
  std::cout << "Search Function Test: ";
  int init[2]{0, 0};
  int goal[2]{4, 5};
  auto board = ReadBoardFile("1.board");
  
  std::cout.setstate(std::ios_base::failbit); // Disable std::cout
  auto output = Search(board, init, goal);
  std::cout.clear(); // Enable cout

  std::vector<std::vector<State>> solution{{State::kStart, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kPath, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kPath, State::kObstacle, State::kEmpty, State::kClosed, State::kClosed, State::kClosed},
                            {State::kPath, State::kObstacle, State::kClosed, State::kPath, State::kPath, State::kPath},
                            {State::kPath, State::kPath, State::kPath, State::kPath, State::kObstacle, State::kFinish}};

  if (output != solution) {
    std::cout << "failed" << "\n";
    std::cout << "Search(board, {0,0}, {4,5})" << "\n";
    std::cout << "Solution board: " << "\n";
    PrintVectorOfVectors(solution);
    std::cout << "Your board: " << "\n";
    PrintVectorOfVectors(output);
    std::cout << "\n";
  } else {
    std::cout << "passed" << "\n";
  }
  return;
}

void TestCheckValidCell() {
  std::cout << "----------------------------------------------------------" << "\n";
  std::cout << "CheckValidCell Function Test: ";
  std::vector<std::vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kClosed, State::kEmpty, State::kEmpty, State::kObstacle, State::kEmpty}};

  if (CheckValidCell(0, 0, grid)) {
    std::cout << "failed" << "\n";
    std::cout << "\n" << "Test grid is: " << "\n";
    PrintVectorOfVectors(grid);
    std::cout << "Cell checked: (0, 0)" << "\n";
    std::cout << "\n";
  } else if (!CheckValidCell(4, 2, grid)) {
    std::cout << "failed" << "\n";
    std::cout << "\n" << "Test grid is: " << "\n";
    PrintVectorOfVectors(grid);
    std::cout << "Cell checked: (4, 2)" << "\n";
    std::cout << "\n";
  } else {
    std::cout << "passed" << "\n";
  }
}

void TestExpandNeighbors() {
  std::cout << "----------------------------------------------------------" << "\n";
  std::cout << "ExpandNeighbors Function Test: ";
  std::vector<int> current{4, 2, 7, 3};
  int goal[2] {4, 5};
  std::vector<std::vector<int>> open{{4, 2, 7, 3}};
  std::vector<std::vector<int>> solution_open = open;
  solution_open.push_back(std::vector<int>{3, 2, 8, 4});
  solution_open.push_back(std::vector<int>{4, 3, 8, 2});
  std::vector<std::vector<State>> grid{{State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kObstacle, State::kEmpty, State::kEmpty, State::kEmpty, State::kEmpty},
                            {State::kClosed, State::kClosed, State::kEmpty, State::kEmpty, State::kObstacle, State::kEmpty}};
  std::vector<std::vector<State>> solution_grid = grid;
  solution_grid[3][2] = State::kClosed;
  solution_grid[4][3] = State::kClosed;
  ExpandNeighbors(current, goal, open, grid);
  CellSort(&open);
  CellSort(&solution_open);
  if (open != solution_open) {
    std::cout << "failed" << "\n";
    std::cout << "\n";
    std::cout << "Your open list is: " << "\n";
    PrintVectorOfVectors(open);
    std::cout << "Solution open list is: " << "\n";
    PrintVectorOfVectors(solution_open);
    std::cout << "\n";
  } else if (grid != solution_grid) {
    std::cout << "failed" << "\n";
    std::cout << "\n";
    std::cout << "Your grid is: " << "\n";
    PrintVectorOfVectors(grid);
    std::cout << "\n";
    std::cout << "Solution grid is: " << "\n";
    PrintVectorOfVectors(solution_grid);
    std::cout << "\n";
  } else {
  	std::cout << "passed" << "\n";
  }
  std::cout << "----------------------------------------------------------" << "\n";
  return;
}
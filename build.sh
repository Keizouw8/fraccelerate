if [[ "$OSTYPE" == "darwin"* ]]; then
    g++ main.cpp -o build/main -std=c++17 -I/opt/homebrew/homebrew/Cellar/sfml/2.5.1_2/include -L/opt/homebrew/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system
fi
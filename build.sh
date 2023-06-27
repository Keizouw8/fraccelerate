if [[ "$OSTYPE" == "darwin"* ]]; then
    g++ main.cpp -I/opt/homebrew/homebrew/Cellar/sfml/2.5.1_2/include -o build/binr
fi
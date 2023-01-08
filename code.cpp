/***********************************************************
*   Автор: Кадесников Михаил                               *
*   Дата: 27.12.2022                                       *
*   Название: Калькулятор длинных чисел                    *
************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

int main() {
  string stringA, stringB;
  char operation;
  
  cout << "введите первое число: ";
  cin >> stringA;
  cout << "введите операцию(+, -, *, /, >, <, =): ";
  cin >> operation;
  cout << "введите второе число: ";
  cin >> stringB;
  
  int sizeFirstNumber = stringA.length();
  int sizeSecondNumber = stringB.length();  
  while(stringA.length() != stringB.length()){
    if(stringA.length() > stringB.length()){
      stringB = "0" + stringB;
    } else{
      stringA = "0" + stringA;
    }  
  }
  stringB = "0" + stringB;
  stringA = "0" + stringA;
  
  int firstNumber[stringA.length()];
  int secondNumber[stringB.length()];
  for (int numberIndex = 0; numberIndex < stringA.length(); ++numberIndex){
    char ch = stringA[numberIndex];
    firstNumber[numberIndex] = ch - '0';
  }
  for (int numberIndex = 0; numberIndex < stringB.length(); ++numberIndex){
    char ch = stringB[numberIndex];
    secondNumber[numberIndex] = ch - '0';
  }

  if(operation == '+') {
    for(int numberIndex = stringA.length() - 1; numberIndex > 0; --numberIndex){
      if((firstNumber[numberIndex] + secondNumber[numberIndex]) > 9){
        firstNumber[numberIndex] = (firstNumber[numberIndex] + secondNumber[numberIndex]) % 10;
        ++firstNumber[numberIndex - 1];
      } else{
        firstNumber[numberIndex] += secondNumber[numberIndex];
      }
    }
    if(firstNumber[0] != 0){
      cout << firstNumber[0];
    }
    for(int numberIndex = 1; numberIndex < stringA.length(); ++numberIndex){
      cout << firstNumber[numberIndex];
    }
    return 0;
  }

  if(operation == '-') {
    for(int index1 = 0; index1 < stringA.length(); ++index1) {
      if((firstNumber[index1] != 0) && (firstNumber[index1] != secondNumber[index1])) {
        if(firstNumber[index1] > secondNumber[index1]) {
          for(int numberIndex = stringA.length() - 1; numberIndex > 0; --numberIndex){
            if((firstNumber[numberIndex] - secondNumber[numberIndex]) < 0) {
              firstNumber[numberIndex] = firstNumber[numberIndex] + 10 - secondNumber[numberIndex];
              --firstNumber[numberIndex - 1];
            } else{
              firstNumber[numberIndex] -= secondNumber[numberIndex];
            }
          }
          for(int numberIndex = 1; numberIndex < stringA.length(); ++numberIndex){
            cout << firstNumber[numberIndex];
          }
          return 0;
        } else{
          for(int numberIndex = stringB.length() - 1; numberIndex > 0; --numberIndex){
            if((secondNumber[numberIndex] - firstNumber[numberIndex]) < 0) {
              secondNumber[numberIndex] = secondNumber[numberIndex] + 10 - firstNumber[numberIndex];
              --secondNumber[numberIndex - 1];
            } else{
              secondNumber[numberIndex] -= firstNumber[numberIndex];
            }
          }
          cout << "-";
          for(int numberIndex = 1; numberIndex < stringB.length(); ++numberIndex){
            cout << secondNumber[numberIndex];
          }
          return 0;
        }
      }
    }
  }

  if(operation == '*'){
    int const range = stringA.length() + stringB.length();
    int ans[range];
    for(int numberIndex = 0; numberIndex < (range); ++numberIndex){
      ans[numberIndex] = 0;
    }
    for(int indexA = 0; indexA < stringA.length(); ++indexA) {
      for(int indexB = 0; indexB < stringB.length(); ++indexB) {
        ans[indexA + indexB] += firstNumber[indexA] * secondNumber[indexB];
        ans[indexA + indexB - 1] = ans[indexA + indexB - 1] + ans[indexA + indexB] / 10;
        ans[indexA + indexB] %= 10;
      }
    }
    for(int numberIndex = range - 1; numberIndex > 0; --numberIndex){
      if(ans[numberIndex] > 9){
        ans[numberIndex - 1] += (ans[numberIndex] / 10);
        ans[numberIndex] = ans[numberIndex] % 10;
      }  
    }
    int wasBefore = 0;
    for(int numberIndex = 0; numberIndex < range - 1; ++numberIndex){
      if(ans[numberIndex] != 0){
        wasBefore = 1;
        }
      if(wasBefore == 1) {
        cout << ans[numberIndex];
      }
    }
    return 0;
  }
  
  if(operation == '/'){
    int zeroBreaker = 0;
    for(int numberIndex = 0; numberIndex < stringB.length(); ++numberIndex){
      if(secondNumber[numberIndex] == 0){
        ++zeroBreaker;
      }
    }
    if(zeroBreaker == stringB.length()){
      cout << "division by zero";
      return -1;
    }
    for(int numberIndex = 0; numberIndex < stringA.length(); ++numberIndex){
      if((firstNumber[numberIndex] != 0) && (firstNumber[numberIndex] != secondNumber[numberIndex])){
        if(firstNumber[numberIndex] < secondNumber[numberIndex]){
          cout << "1";
          return 0;
        } else{
          break;
        }
      }
    }
    
    int rangeC = sizeFirstNumber - sizeSecondNumber + 1;
    int answer[rangeC + 1];
    for(int numberIndex = 0; numberIndex < rangeC + 1; ++numberIndex){
      answer[numberIndex] = 0;
    }
    
    while(true){
      ++answer[rangeC];
      for(int numberIndex = rangeC; numberIndex > 0; --numberIndex){
        if(answer[numberIndex] == 10){
          answer[numberIndex] = 0;
          ++answer[numberIndex - 1];
        }
      }
      int rangeANS = (rangeC + 1) + stringB.length();
      int expectedAnswer[rangeANS];
      for(int numberIndex = 0; numberIndex < rangeANS; ++numberIndex){
        expectedAnswer[numberIndex] = 0;
      }
      for(int indexC = 0; indexC < (rangeC + 1); ++indexC) {
        for(int indexB = 0; indexB < stringB.length(); ++indexB) {
          expectedAnswer[indexC + indexB] += answer[indexC] * secondNumber[indexB];
          expectedAnswer[indexC + indexB - 1] = expectedAnswer[indexC + indexB - 1] + expectedAnswer[indexC + indexB] / 10;
          expectedAnswer[indexC + indexB] %= 10;
        }
      }
      for(int numberIndex = rangeANS - 1; numberIndex > 0; --numberIndex){
        if(expectedAnswer[numberIndex] > 9){
          expectedAnswer[numberIndex - 1] += (expectedAnswer[numberIndex] / 10);
          expectedAnswer[numberIndex] = expectedAnswer[numberIndex] % 10;
        }  
      }
      int leadingZeros = 0;
      while(expectedAnswer[leadingZeros] == 0){
        ++leadingZeros;
      }
      int hitCount = 0;
      for(int numberIndex = 0; numberIndex < stringA.length(); ++numberIndex){
        int const qe = numberIndex + rangeC + 1 - leadingZeros;
        if(expectedAnswer[qe + leadingZeros - 1] == firstNumber[numberIndex]){
          ++hitCount;
        } else{
          if(expectedAnswer[qe + leadingZeros - 1] >= firstNumber[numberIndex]){
            for(int numberIndex = 0; numberIndex < rangeC + 1; ++numberIndex){
              cout << answer[numberIndex];
            }
            return 0;
          }
          if(expectedAnswer[qe + leadingZeros - 1] <= firstNumber[numberIndex]) {
            break;
          }
        }
      }
      if(hitCount == stringA.length()) {
        for(int numberIndex = 0; numberIndex < rangeC + 1; ++numberIndex){
          cout << answer[numberIndex];
        }
      return 0;
      }
    }
  }

  if(operation == '>'){
    for(int numberIndex = 0; numberIndex < stringA.length(); ++numberIndex){
      if((firstNumber[numberIndex] != 0) && (firstNumber[numberIndex] != secondNumber[numberIndex])){
        if(firstNumber[numberIndex] > secondNumber[numberIndex]){
          cout << "true";
          return 0;
        } else{
          cout << "false";
          return 0;
        }
      }
    }
    if(firstNumber[stringA.length() - 1] == secondNumber[stringA.length() - 1]){
       cout << "true";
       return 0;
    }
  }

  if(operation == '<'){
    for(int numberIndex = 0; numberIndex < stringA.length(); ++numberIndex){
      if((firstNumber[numberIndex] != 0) && (firstNumber[numberIndex] != secondNumber[numberIndex])){
        if(firstNumber[numberIndex] < secondNumber[numberIndex]){
          cout << "true";
          return 0;
        } else{
          cout << "false";
          return 0;
        }
      }
    }
    if(firstNumber[stringA.length() - 1] == secondNumber[stringA.length() - 1]){
       cout << "false";
       return 0;
    }
  }

  if(operation == '='){
    int tracker = 0;
    for(int numberIndex = 0; numberIndex < stringA.length(); ++numberIndex){
      if(firstNumber[numberIndex] == secondNumber[numberIndex]){
        tracker = 1;
      } else{
        cout << "false";
        return 0;
      }
    }
    if(tracker = 1){
      cout << "true";
    }
  }
}

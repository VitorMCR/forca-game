## Edite o .txt para adicionar/remover palavras!

### Retornos
| Int | Descrição |
| --- | --- |
| `0` | Usuário perdeu o jogo |
| `1` | Usuário ganhou o jogo |

### Exemplo de Uso
```c
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "forcagame.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    printf("Olá mundo!\n");
    system("pause");

    int res = ForcaGame();
    system("cls");
    if (res) {
        printf("Parabéns, você ganhou!\n\n");
    } else {
        printf("Que pena... Mais sorte na próxima!\n\n");
    }

    return 0;
}
```

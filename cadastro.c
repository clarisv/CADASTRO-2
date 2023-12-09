#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USUARIOS 1000

/*struct para o cadastro de usuarios **/
typedef struct
{
    int id;
    char nome[50];
    char email[50];
    char sexo;
    char endereco[100];
    double altura;
    int vacina;

} Usuario;


void clearInputBuffer();
int validarEmail(const char email[]);
void cadastrar(Usuario usuarios[], int *totalCadastros);
void imprimir(const Usuario usuarios[], int totalCadastrados);
void buscarEmail(const Usuario usuarios[], int totalCadastros, const char email[]);
void editar(Usuario usuarios[], int totalCadastrados, int id);
void excluir(Usuario usuarios[], int *totalCadastrados, int id);


int main()
{
    srand((unsigned int)time(NULL));

    Usuario usuarios[USUARIOS];
    int totalCadastros = 0;

    char opcao;

    do
    {
        printf("\nopcoes\n");
        printf("1: cadastrar\n");
        printf("2: imprimir\n");
        printf("3: buscar pelo e-mail\n");
        printf("4: editar\n");
        printf("5: excluir\n");
        printf("0: sair\n");

        printf("escolha a opcao desejada: ");
        scanf(" %c", &opcao);

        switch (opcao)
        {
        case '1':
            cadastrar(usuarios, &totalCadastros);
            break;
        case '2':
            imprimir(usuarios, totalCadastros);
            break;
        case '3':
            printf("informe o e-mail a ser buscado: ");
            char buscaEmail[50];
            scanf(" %s", buscaEmail);
            buscarEmail(usuarios, totalCadastros, buscaEmail);
            break;
        case '4':
            printf("informe o ID do usuario a ser editado: ");
            int idEditar;
            scanf("%d", &idEditar);
            editar(usuarios, totalCadastros, idEditar);
            break;
        case '5':
            printf("informe o ID do usuario a ser excluido: ");
            int idExcluir;
            scanf("%d", &idExcluir);
            excluir(usuarios, &totalCadastros, idExcluir);
            break;
        case '0':
            printf("saiu do programa\n");
            break;
        default:
            printf("opcao invalida! Tente novamente\n");
        }
    } while (opcao != '0');

    return 0;
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int validarEmail(const char email[])
{
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            printf("e-mail validado\n");
            return 1;
        }
    }

    printf("e-mail invalido! tente novamente\n");
    return 0;
}

void cadastrar(Usuario usuarios[], int *totalCadastros)
{
    if (*totalCadastros >= USUARIOS)
    {
        printf("limite de usuarios atingido.\n");
        return;
    }

    usuarios[*totalCadastros].id = rand() % 1000 + 1;

    printf("informe o nome: ");
    clearInputBuffer();
    fgets(usuarios[*totalCadastros].nome, sizeof(usuarios[*totalCadastros].nome), stdin);
    usuarios[*totalCadastros].nome[strcspn(usuarios[*totalCadastros].nome, "\n")] = '\0';

    while (!validarEmail(usuarios[*totalCadastros].email))
    {
        printf("informe o e-mail:");
        fgets(usuarios[*totalCadastros].email, sizeof(usuarios[*totalCadastros].email), stdin);
        usuarios[*totalCadastros].email[strcspn(usuarios[*totalCadastros].email, "\n")] = '\0';
    }

    printf("informe o genero (M, F ou I): ");
    scanf(" %c", &usuarios[*totalCadastros].sexo);

    printf("informe o endereco:");
    clearInputBuffer();
    fgets(usuarios[*totalCadastros].endereco, sizeof(usuarios[*totalCadastros].endereco), stdin);
    usuarios[*totalCadastros].endereco[strcspn(usuarios[*totalCadastros].endereco, "\n")] = '\0';

    printf("informe a altura: ");
    scanf("%lf", &usuarios[*totalCadastros].altura);

    printf("informe se tomou a vacina (1 para sim, 0 para nao): ");
    scanf("%d", &usuarios[*totalCadastros].vacina);

    (*totalCadastros)++;
}

void imprimir(const Usuario usuarios[], int totalCadastrados)
{
    if (totalCadastrados == 0)
    {
        printf("cadastro de usuarios vazio\n");
        return;
    }

    printf("\nLista de usuarios\n");
    for (int i = 0; i < totalCadastrados; i++)
    {
        printf("ID: %d\n", usuarios[i].id);
        printf("nome: %s\n", usuarios[i].nome);
        printf("email: %s\n", usuarios[i].email);
        printf("sexo: %c\n", usuarios[i].sexo);
        printf("endereco: %s\n", usuarios[i].endereco);
        printf("altura: %.2lf metros\n", usuarios[i].altura);
        printf("vacina: %s\n", usuarios[i].vacina ? "Tomou" : "Nao tomou");
        printf("\n");
    }
}

void buscarEmail(const Usuario usuarios[], int totalCadastros, const char email[])
{
    if (totalCadastros == 0)
    {
        printf("cadastro de usuarios vazio\n");
        return;
    }

    int encontrado = 0;

    for (int i = 0; i < totalCadastros; i++)
    {
        if (strcmp(usuarios[i].email, email) == 0)
        {
            printf("usuario encontrado:\n");
            printf("ID: %d\n", usuarios[i].id);
            printf("nome: %s\n", usuarios[i].nome);
            printf("email: %s\n", usuarios[i].email);
            printf("sexo: %c\n", usuarios[i].sexo);
            printf("endereco: %s\n", usuarios[i].endereco);
            printf("altura: %.2lf metros\n", usuarios[i].altura);
            printf("vacina: %s\n", usuarios[i].vacina ? "Tomou" : "Nao tomou");
            printf("\n");

            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("usuario com o e-mail %s nao encontrado.\n", email);
    }
}

void editar(Usuario usuarios[], int totalCadastrados, int id)
{
    printf("editando usuario ID %d\n", id);

    for (int i = 0; i < totalCadastrados; i++)
    {
        if (usuarios[i].id == id)
        {
            int opcao;

            do
            {
                printf("\nescolha a opcao que deseja editar\n");
                printf("1: nome\n");
                printf("2: e-mail\n");
                printf("3: sexo\n");
                printf("4: endereco\n");
                printf("5: altura\n");
                printf("6: vacina\n");
                printf("7: alterar cadastro inteiro\n");
                printf("0: sair\n");
                printf("opcao:");
                scanf("%d", &opcao);

                switch (opcao)
                {
                case 1:
                    printf("informe o novo nome: ");
                    clearInputBuffer();
                    fgets(usuarios[i].nome, sizeof(usuarios[i].nome), stdin);
                    usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = '\0';
                    break;
                case 2:
                    printf("informe o novo e-mail (ou '0' para sair): ");
                    clearInputBuffer();
                    fgets(usuarios[i].email, sizeof(usuarios[i].email), stdin);
                    usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';
                    if (strcmp(usuarios[i].email, "0") == 0)
                    {
                        break; // Sair da edicao de e-mail
                    }
                    while (!validarEmail(usuarios[i].email))
                    {
                        printf("informe o novo e-mail (ou '0' para sair): ");
                        fgets(usuarios[i].email, sizeof(usuarios[i].email), stdin);
                        usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';
                        if (strcmp(usuarios[i].email, "0") == 0)
                        {
                            break; // Sair da edicao de e-mail
                        }
                    }
                    break;
                case 3:
                    printf("informe o novo sexo (M/F): ");
                    clearInputBuffer();
                    scanf(" %c", &usuarios[i].sexo);
                    break;
                case 4:
                    printf("informe o novo endereco:");
                    clearInputBuffer();
                    fgets(usuarios[i].endereco, sizeof(usuarios[i].endereco), stdin);
                    usuarios[i].endereco[strcspn(usuarios[i].endereco, "\n")] = '\0';
                    break;
                case 5:
                    printf("informe a nova altura:");
                    scanf("%lf", &usuarios[i].altura);
                    break;
                case 6:
                    printf("informe se tomou a vacina (1 para sim, 0 para nao): ");
                    scanf("%d", &usuarios[i].vacina);
                    break;
                case 7:
                    printf("\neditando cadastro inteiro do usuario ID %d\n", id);
                    cadastrar(usuarios, &totalCadastrados);
                    return;
                case 0:
                    printf("saindo da edicao.\n");
                    break;
                default:
                    printf("opcao invalida! tente novamente.\n");
                }
            } while (opcao != 0);

            printf("cadastro atualizado com sucesso!\n");
            return;
        }
    }

    printf("usuario ID %d nao encontrado!\n", id);
}

void excluir(Usuario usuarios[], int *totalCadastrados, int id)
{
    if (*totalCadastrados == 0)
    {
        printf("cadastro de usuarios vazio\n");
        return;
    }

    for (int i = 0; i < *totalCadastrados; i++)
    {
        if (usuarios[i].id == id)
        {
            for (int j = i; j < *totalCadastrados - 1; j++)
            {
                usuarios[j] = usuarios[j + 1];
            }
            (*totalCadastrados)--;
            printf("usuario ID %d excluido com sucesso!\n", id);
            return;
        }
    }

    printf("usuario ID %d nao encontrado!\n", id);
}

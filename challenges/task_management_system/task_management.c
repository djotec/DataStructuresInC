#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó que representa uma tarefa
typedef struct task
{
    char description[50];
    struct task *proximo;
} Task;

// Função para criar uma nova tarefa
Task *createTask(char *description)
{
    Task *taskN = (Task *)malloc(sizeof(Task));
    if (taskN != NULL)
    {
        strcpy(taskN->description, description);
        taskN->proximo = NULL;
    }
    return taskN;
}

// Função para adicionar uma nova tarefa ao final da lista
void addTask(Task **head, char *description)
{
    Task *taskN = createTask(description);
    if (*head == NULL)
    {
        *head = taskN;
    }
    else
    {
        Task *temp = *head;
        while (temp->proximo != NULL)
        {
            temp = temp->proximo;
        }
        temp->proximo = taskN;
    }
}

// Função para remover uma tarefa específica
void removeTask(Task **head, char *description)
{
    Task *taskN = *head;
    Task *prev = NULL;

    if (taskN != NULL && strcmp(taskN->description, description) == 0)
    {
        *head = taskN->proximo;
        free(taskN);
        return;
    }

    // Procurar a tarefa a ser removida
    while (taskN != NULL && strcmp(taskN->description, description) != 0)
    {
        prev = taskN;
        taskN = taskN->proximo;
    }

    // Se a tarefa não foi encontrada
    if (taskN == NULL)
        return;

    // Desvincular a tarefa da lista
    prev->proximo = taskN->proximo;
    free(taskN);
}

// Função para buscar uma tarefa na lista
Task *searchTask(Task *head, char *description)
{
    Task *current = head;
    while (current != NULL)
    {
        if (strcmp(current->description, description) == 0)
        {
            return current;
        }
        current = current->proximo;
    }
    return NULL;
}

// Função para exibir todas as tarefas pendentes
void displayTasks(Task *head)
{
    Task *current = head;
    if (current == NULL)
    {
        printf("Nenhuma tarefa pendente.\n");
        return;
    }
    while (current != NULL)
    {
        printf("%s\n", current->description);
        current = current->proximo;
    }
}

int main()
{
    Task *head = NULL;
    int opcao;
    char description[100];

    do
    {
        printf("\n=============================\n");
        printf("\nMENU GESTÃO DE TAREFAS:\n");
        printf("\n=============================\n");
        printf("1. Adicionar nova tarefa\n");
        printf("2. Remover tarefa\n");
        printf("3. Buscar tarefa\n");
        printf("4. Exibir todas as tarefas\n");
        printf("0. Sair\n");
        printf("---------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao)
        {
        case 1:
            printf("Digite a descrição da tarefa: ");
            fgets(description, sizeof(description), stdin);
            description[strcspn(description, "\n")] = 0; // Remover nova linha
            addTask(&head, description);
            break;
        case 2:
            printf("\nDigite a descrição da tarefa a ser removida: ");
            fgets(description, sizeof(description), stdin);
            description[strcspn(description, "\n")] = 0; // Remover nova linha
            removeTask(&head, description);
            break;
        case 3:
            printf("Digite a descrição da tarefa a ser buscada: ");
            fgets(description, sizeof(description), stdin);
            description[strcspn(description, "\n")] = 0; // Remover nova linha
            Task *foundTask = searchTask(head, description);
            if (foundTask != NULL)
            {
                printf("Tarefa encontrada: %s\n", foundTask->description);
            }
            else
            {
                printf("Tarefa não encontrada.\n");
            }
            break;
        case 4:

            printf("\n=============================\n");
            printf("\nTAREFAS:\n");
            printf("\n=============================\n");
            displayTasks(head);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    // Liberar memória alocada
    Task *current = head;
    Task *proximo;
    while (current != NULL)
    {
        proximo = current->proximo;
        free(current);
        current = proximo;
    }

    return 0;
}

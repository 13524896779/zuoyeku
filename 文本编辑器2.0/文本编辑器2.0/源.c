#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000 // ��������ı�����
#define MAX_OPS 100   // ������������

// �ı��༭���ṹ�壬���ڴ洢�ı�����
typedef struct {
    char* text;       // �洢�ı�������
    int len;          // ��ǰ�ı�����
    int capacity;     // �ı����������
} TextEditor;

// ���������������Ľṹ�壬���ڼ�¼������Ϣ
typedef struct {
    int position;     // ������λ��
    char character;   // �������ַ�
} UndoRedoOp;

// ջ�ṹ�壬����ʵ�ֳ�������������
typedef struct {
    UndoRedoOp ops[MAX_OPS]; // �洢����������
    int top;                // ջ��λ��
} Stack;

// ��ʼ��ջ
void initStack(Stack* s) {
    s->top = -1;
}

// �ж�ջ�Ƿ�����
int isFull(Stack* s) {
    return s->top == MAX_OPS - 1;
}

// �ж�ջ�Ƿ�Ϊ��
int isEmpty(Stack* s) {
    return s->top == -1;
}

// ��ջ��ѹ��һ������
void push(Stack* s, UndoRedoOp op) {
    if (isFull(s)) {
        printf("ջ����\n");
        return;
    }
    s->ops[++s->top] = op;
}

// ��ջ�е���һ������
UndoRedoOp pop(Stack* s) {
    if (isEmpty(s)) {
        UndoRedoOp op = { -1, '\0' };
        return op;
    }
    return s->ops[s->top--];
}

// ��ʼ���ı��༭��
void initTextEditor(TextEditor* editor) {
    editor->text = (char*)malloc(MAX_SIZE * sizeof(char));
    editor->len = 0;
    editor->capacity = MAX_SIZE;
}

// �ͷ��ı��༭����Դ
void freeTextEditor(TextEditor* editor) {
    free(editor->text);
}

// ��ָ��λ�ò����ַ�
void insertChar(TextEditor* editor, int position, char character) {
    if (editor->len >= editor->capacity) {
        printf("�ı��༭������\n");
        return;
    }
    memmove(editor->text + position + 1, editor->text + position, editor->len - position + 1);
    editor->text[position] = character;
    editor->len++;
}

// ɾ��ָ��λ�õ��ַ�
void deleteChar(TextEditor* editor, int position) {
    if (position < 0 || position >= editor->len) {
        printf("��Ч��λ��\n");
        return;
    }
    memmove(editor->text + position, editor->text + position + 1, editor->len - position);
    editor->len--;
}

// �������һ�β���
void undo(TextEditor* editor, Stack* undoStack, Stack* redoStack) {
    if (isEmpty(undoStack)) {
        printf("û�в������Գ���\n");
        return;
    }
    UndoRedoOp op = pop(undoStack);
    push(redoStack, op);
    if (op.position == -1) {
        insertChar(editor, op.position, op.character);
    }
    else {
        deleteChar(editor, op.position);
    }
}

// �������һ�γ����Ĳ���
void redo(TextEditor* editor, Stack* undoStack, Stack* redoStack) {
    if (isEmpty(redoStack)) {
        printf("û�в�����������\n");
        return;
    }
    UndoRedoOp op = pop(redoStack);
    push(undoStack, op);
    if (op.position == -1) {
        deleteChar(editor, op.position);
    }
    else {
        insertChar(editor, op.position, op.character);
    }
}

// ��¼����������ջ
void recordOperation(Stack* undoStack, int position, char character, int type) {
    UndoRedoOp op;
    op.position = position;
    op.character = character;
    push(undoStack, op);
}

// ��ӡ��ǰ�ı�����
void printText(TextEditor* editor) {
    printf("��ǰ�ı�: %s\n", editor->text);
}

// �����ı����ļ�
void saveText(TextEditor* editor, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("�޷����ļ�����д��\n");
        return;
    }
    fwrite(editor->text, sizeof(char), editor->len, file);
    fclose(file);
    printf("�ı��ѱ��浽�ļ� %s\n", filename);
}

// ���ļ������ı�
void loadText(TextEditor* editor, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ����ж�ȡ\n");
        return;
    }
    editor->len = fread(editor->text, sizeof(char), editor->capacity, file);
    fclose(file);
    printf("�ı��Ѵ��ļ� %s ����\n", filename);
}

// ��ӡ�����˵�
void printMenu() {
    printf("�ı��༭���˵���\n");
    printf("1. �����ַ�\n");
    printf("2. ɾ���ַ�\n");
    printf("3. ����\n");
    printf("4. ����\n");
    printf("5. ��ӡ�ı�\n");
    printf("6. �����ı����ļ�\n");
    printf("7. ���ļ������ı�\n");
    printf("8. �˳�\n");
    printf("���������ѡ��");
}

// �����������ڲ����ı��༭������
int main() {
    TextEditor editor;
    initTextEditor(&editor);
    Stack undoStack, redoStack;
    initStack(&undoStack);
    initStack(&redoStack);

    char buffer[MAX_SIZE];
    int choice, position;
    char character;
    while (1) {
        printMenu();
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("��ȡ����ʧ��\n");
            continue;
        }
        if (sscanf(buffer, "%d", &choice) != 1) {
            printf("��Ч������\n");
            continue;
        }
        switch (choice) {
        case 1:
            printf("������Ҫ�����λ�ú��ַ���");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("��ȡ����ʧ��\n");
                continue;
            }
            if (sscanf(buffer, "%d %c", &position, &character) != 2) {
                printf("��Ч������\n");
                continue;
            }
            insertChar(&editor, position, character);
            recordOperation(&undoStack, position, character, 1);
            printText(&editor);
            break;
        case 2:
            printf("������Ҫɾ����λ�ã�");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("��ȡ����ʧ��\n");
                continue;
            }
            if (sscanf(buffer, "%d", &position) != 1) {
                printf("��Ч������\n");
                continue;
            }
            character = editor.text[position];
            deleteChar(&editor, position);
            recordOperation(&undoStack, position, character, 0);
            printText(&editor);
            break;
        case 3:
            undo(&editor, &undoStack, &redoStack);
            printText(&editor);
            break;
        case 4:
            redo(&editor, &undoStack, &redoStack);
            printText(&editor);
            break;
        case 5:
            printText(&editor);
            break;
        case 6:
            printf("������Ҫ������ļ�����");
            fgets(buffer, sizeof(buffer), stdin);
            saveText(&editor, buffer);
            break;
        case 7:
            printf("������Ҫ���ص��ļ�����");
            fgets(buffer, sizeof(buffer), stdin);
            loadText(&editor, buffer);
            printText(&editor);
            break;
        case 8:
            freeTextEditor(&editor);
            return 0;
        default:
            printf("��Ч��ѡ��\n");
        }
    }
}
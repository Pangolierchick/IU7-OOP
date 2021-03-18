#include <QMessageBox>
#include "error.hpp"

void error_manager(int errnum) {
    switch (errnum) {
        case READ_ERROR:
            QMessageBox::critical(NULL, "Ошибка", "Произошла ошибка при чтении файла.");
            break;
        
        case ALLOC_ERROR:
            QMessageBox::critical(NULL, "Ошибка", "Произошла ошибка выделения памяти.");
            break;
        
        case WRITE_ERROR:
            QMessageBox::critical(NULL, "Ошибка", "Произошла ошибка записи в файл.");
            break;
        
        case BAD_DOTS_NUM:
            QMessageBox::critical(NULL, "Ошибка", "Введенно неправильное кол-во точек.");
            break;
        
        case BAD_EDGES_NUM:
            QMessageBox::critical(NULL, "Ошибка", "Введенно неправильное кол-во ребер.");
            break; 
        
        case BAD_DOTS:
            QMessageBox::critical(NULL, "Ошибка", "Точки должны быть заданы действительными числами.");
            break;

        case BAD_EDGES:
            QMessageBox::critical(NULL, "Ошибка", "Связи должны быть заданы целыми числами.");
            break;
    }
}

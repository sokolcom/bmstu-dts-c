/* Лабораторная работа №1
 * ТиСД
 * Вараинт №22
 */

#include <stdio.h>
#include <string.h>

// Return codes
#define SUCCESS 0
#define EMPTY_ERROR -10
#define INPUT_ERROR -20
#define LENGTH_LIMIT_ERROR 1
#define NULL_ERROR 10
#define DIVISOR_FORM_ERROR 20
#define ZERO_DIVISION_ERROR 25
#define MANT_LENGTH_ERROR 30
#define EXP_LENGTH_ERROR 40
#define EXP_OVERFLOW 45

// Consts
#define MAX_LENGTH 40  // as 30 + 1 + 1 + 5 + '\0' + "прозапас"
#define MAX_MANTISSA 30
#define MAX_EXPONENT 5

#define DIVIDEND_TYPE 1
#define DIVISOR_TYPE -1

#define TRUE 1
#define FALSE 0

#define PLUS '+'
#define MINUS '-'

#define NO_SIGN 0
#define YES_SIGN 1

#define SIGN 1
#define BEFORE_POINT 2
#define AFTER_POINT 3
#define IS_EXPONENT 4
#define EXP_SIGN 5
#define EXPONENT 6 

#define BASE 10

#define MAX_EXP 99999
#define MIN_EXP -99999

// Структура, в которой хранится длинные числа
typedef struct
{
    char sign;
    char mantissa[MAX_MANTISSA + 2]; // 30 + точка + '\0'
    int exponent;
} num_t;


// Информация для пользователя
void welcome()
{
    printf("PRO calculator v1.0\n\n");
    printf("About:\n");
    printf("Program to divide extra-large decimal numbers\n");
    printf("Dividend is fractional, divisor is integer\n");
    printf("Answer will be given in normalized notation\n\n");

    printf("How to use it?\n");
    printf("* DIVIDEND should be entered as 1...9e1..5\n");
    printf("*    Length of the mantissa shouldn't be more than 30 digits\n");
    printf("*    Length of the exponent shouldn't be more than 5 digits\n");
    printf("*    Use '.' (dot) to enter fractional numbers\n");
    printf("*    Use latin 'e' to enter exponent\n");
    printf("* DIVISOR is an integer, not longer than 30 digits\n");
    printf("* Entering spaces (' ') is forbidden\n\n");
    
    printf("Have FUN!\n\n");
}


// Ввод чисел пользователем
int input_number(char* input_data, const int input_type)
{
    char temp_symbol = getchar();
    int temp_pos = 0;
    int nulls_before_point = 0;
    int data_equals_null = TRUE; // Для проверки на нули в старших разрядах

    if (temp_symbol == '\n')
        return EMPTY_ERROR;

    while ((temp_pos < MAX_LENGTH) && (temp_symbol != '\n') && (temp_symbol != EOF))
    {
        if ((temp_symbol == '0') && (data_equals_null) && (nulls_before_point >= 1))
            return NULL_ERROR;

        if ((input_type ==  DIVISOR_TYPE) && ((temp_symbol == '.') || (temp_symbol == 'e')))
            return DIVISOR_FORM_ERROR;

        if (data_equals_null && (temp_symbol == '0'))
        {
            if (input_type == DIVISOR_TYPE)
                return ZERO_DIVISION_ERROR;
            else
            {
                temp_symbol = getchar();
                nulls_before_point++;
                continue;
            }
        }

        if (data_equals_null && (temp_symbol != '0'))
            data_equals_null = FALSE;

        input_data[temp_pos++] = temp_symbol;
        temp_symbol = getchar();
    }

    input_data[temp_pos] = '\0';

    if (temp_pos == MAX_LENGTH)
        return LENGTH_LIMIT_ERROR;

    return SUCCESS;
}


// Проверка, является ли символ числом?
int is_digit(const char symbol)
{
    if ((symbol >= '0') && (symbol <= '9'))
        return TRUE;
    return FALSE;
}

// Проверяет на корректность ввода
int check_data(char* data)
{
    int case_code = SIGN;
    int dividend_point = FALSE;  // Показывает была ли точка в мантиссе
    int temp_mant_length = 0;
    int temp_exp_length = 0;
    char sign = NO_SIGN;

    /* case SIGN - знак мантиссы
    * case BEFORE_POINT - число/точка мантиссы
    * case AFTER_POINT - часть мантиссы после точки
    * case IS_EXPONENT - проверка наличия порядка числа
    * case EXP_SIGN - знак порядка числа
    * case EXPONENT - порядок числа */
    for (int i = 0; data[i]; i++)
    {
        switch (case_code)
        {
            case SIGN:
                // Введен знак мантиссы
                if ((data[i] == '+') || (data[i] == '-'))
                {
                    case_code = BEFORE_POINT;
                    sign = YES_SIGN;
                    break;
                }

                // Знак отсутсвует
                if (is_digit(data[i]))
                {
                    temp_mant_length++;
                    case_code = BEFORE_POINT;
                }
                // Прочитана точка
                else if (data[i] == '.')
                    case_code = AFTER_POINT;
                // Мантисса отсутвует
                else if (data[i] == 'e')
                    case_code = EXP_SIGN;
                // Некорректный ввод
                else
                    return INPUT_ERROR;
                break;

            case BEFORE_POINT:
                // Проверка длины мантиссы
                if ((i >= sign + MAX_MANTISSA) && (data[i] != 'e') && (data[i] != '.'))
                    return MANT_LENGTH_ERROR;

                // Далее следует порядок
                if (data[i] == 'e')
                    case_code = EXP_SIGN;
                else if (data[i] == '.')
                    case_code = AFTER_POINT;
                else if (!is_digit(data[i]))
                    return INPUT_ERROR;
                break;

            case AFTER_POINT:
                dividend_point = TRUE;
                if (is_digit(data[i]))
                {
                    temp_mant_length++;
                    case_code = IS_EXPONENT;
                }
                else
                {
                    if (data[i] == '\0')
                        return SUCCESS;
                    else if (data[i] == 'e')
                        case_code = IS_EXPONENT;
                    else
                        return INPUT_ERROR;
                }

            case IS_EXPONENT:
                if (data[i] == 'e')
                {
                    if ((i >= sign + dividend_point + MAX_MANTISSA) && (data[i] != 'e') && (data[i] != '.'))
                        return MANT_LENGTH_ERROR;
                    case_code = EXP_SIGN;
                }
                else if (!is_digit(data[i]))
                    return INPUT_ERROR;
                break;

            case EXP_SIGN:
                if ((data[i] == '+') || (data[i] == '-'))
                    case_code = EXPONENT;
                
                if (is_digit(data[i]))
                {
                    temp_exp_length++;
                    case_code = EXPONENT;
                }
                else if ((data[i] != '-') && (data[i] != '+'))
                    return INPUT_ERROR;
                break;

            case EXPONENT:
                if(!is_digit(data[i]))
                    return INPUT_ERROR;
                else
                    temp_exp_length++;
                if (temp_exp_length > MAX_EXPONENT)
                    return EXP_LENGTH_ERROR;
                break;

            default:
                return EXP_LENGTH_ERROR;
        }
    }
    return SUCCESS;
}


//Приведение числа к нормализованному виду в структуре num_t
void parse_number(char* data, num_t* number)
{
    int point = FALSE; // Флаг, который поднимается если в мантиссе есть точка
    int no_mantissa_flag = FALSE; // Флаг, который поднимается если мантисса не была введена
    int data_pos = 0;
    int mant_pos = 0;

    if (data[data_pos] == '-')
        number->sign = MINUS; // Записываем знак минуса в отельное поле структуры

    if (data[data_pos] == '-' || data[data_pos] == '+')
        data_pos++;
    // Если ни знака, ни значения не было введено, то по умочанию значение приравнивается 1
    else if (data[data_pos] == 'e')
    {
        strcpy(number->mantissa, ".1000000000000000000000000000000\0");
        no_mantissa_flag = TRUE;
    }

    // Запись в мантиссу
    while (((is_digit(data[data_pos]) || (data[data_pos] == '.')) && (mant_pos < MAX_MANTISSA + 1)))
    {
        // Отмечаем точку в мантиссе, при её наличии
        if (data[data_pos] == '.')
            point = TRUE;
        number->mantissa[mant_pos++] = data[data_pos++];
    }

    // Даже если точки не было введено, вставляем ее в конец - нормализуем запись
    if (point == FALSE)
        number->mantissa[mant_pos++] = '.';

    // Дополняем мантиссу нулями (если не все разярды заняты)
    while (mant_pos < MAX_MANTISSA + 1)
        number->mantissa[mant_pos++] = '0';

    number->mantissa[mant_pos] = '\0';

    int exp_sign = 1; // Знак порядка по умолчанию (потом на него домножим экспоненту)
    if (data[data_pos] == 'e')
        data_pos++;

    if (data[data_pos] == '+') // Проверка знака порядка
        data_pos++;
    else if (data[data_pos] == '-')
    {
        exp_sign = -1;
        data_pos++;
    }

    // Считывание порядка
    number->exponent = 0;
    while (data[data_pos])
        number->exponent = number->exponent * BASE + (int)(data[data_pos++] - '0');

    number->exponent += no_mantissa_flag;
    number->exponent *= exp_sign;

    //Преобразуем мантиссу к виду .(0)xxxxx...
    int point_pos = 0;
    // Поиск позиции точки
    while (number->mantissa[point_pos] != '.')
        point_pos++;

    // Увеличение порядка (из-за сдвига точки)
    number->exponent += point_pos;

    while (point_pos > 0)
    {
        number->mantissa[point_pos] = number->mantissa[point_pos - 1];
        point_pos--;
    }
    // Чтобы следить за переполнением, заменим точку нулем
    number->mantissa[point_pos] = '0';
}


// Сравнивает мантиссы
// Возвращает TRUE если DIVDEND >= DIVISOR, в противном случае FALSE
int compare_mantissa(num_t dividend, num_t divisor) 
{
    for (int i = 0; dividend.mantissa[i]; i++)
    {
        if ((int)(dividend.mantissa[i] - divisor.mantissa[i]) > 0 )
            return TRUE;

        if ((int)(dividend.mantissa[i] - divisor.mantissa[i]) < 0)
            return FALSE;
    }
    return TRUE;
}


// Сдвиг мантиссы влево
void left_shift(num_t* number)
{
    int shift = 1;
    // По факту можно было упростить условие, но чтобы логика была яснее оставим так
    for (int i = 0; i < MAX_MANTISSA + 1 - shift; i++)
        number->mantissa[i] = number->mantissa[i + shift];
    number->mantissa[MAX_MANTISSA + 1 - shift] = '0';
}


// Проверка на то, только ли нули в мантиссе
int equal_zero(char* mantissa)
{
    for (int i = 0; i < MAX_MANTISSA + 1; i++)
        if (mantissa[i] != '0')
            return FALSE;
    return TRUE;
}


int subtraction(num_t* dividend, num_t divisor)
{
    // Если делитель больше делимого, выходим
    if (compare_mantissa(*dividend, divisor) == FALSE)
        return FALSE;

    // Вычитание "в столбик"
    for (int i = strlen(divisor.mantissa) - 1; i >= 0; i--)
    {
        // Если следует "занять":
        if (dividend->mantissa[i] - divisor.mantissa[i] < 0)
        {
            int occupied = i - 1;
            while (dividend->mantissa[occupied] - '0' == 0)
                occupied--;

            dividend->mantissa[occupied]--;
            occupied++;

            // Обновление разрядов делителя
            while (occupied < i)
                dividend->mantissa[occupied++] += 9;

            // Вычитание в occupied разряде
            dividend->mantissa[i] += BASE - (divisor.mantissa[i] - '0');
        }
        // Если "занимать" не надо:
        else
            dividend->mantissa[i] -= divisor.mantissa[i] - '0';
    }
    return TRUE;
}


int count_multiplier(num_t* dividend, const num_t divisor)
{
    int multiplier = 0;
    while (subtraction(dividend, divisor) == TRUE)
        multiplier++;

    // Сдвиг мантиссы (по сути, снос следующего числа)
    left_shift(dividend);

    return multiplier;
}


num_t compute_quotient(num_t dividend, num_t divisor)
{
    num_t quotient;
    strcpy(quotient.mantissa, "0");
    quotient.exponent = 0;
    
    // Если делимое равно нулю
    if (equal_zero(dividend.mantissa))
        return quotient;

    // Если делимое меньше делителя, то вычитаем из экспоненты единицу
    if (compare_mantissa(dividend, divisor) ==  FALSE)
    {
        dividend.exponent--;
        left_shift(&dividend);
    }
    quotient.mantissa[0] = '0';

    // Находим первую цифру частного
    int digit = count_multiplier(&dividend, divisor);
    quotient.mantissa[1] = digit + '0';
    
    // Деление "в столбик"
    int i;
    for (i = 2; i < MAX_MANTISSA + 1; i++)
    {
        // Если в конце в остатке ноль - поделилось нацело, конец
        if (equal_zero(dividend.mantissa))
        {
            digit = 0;
            quotient.mantissa[i] = '\0';
            break;
        }

        // Если невозможно вычесть, записываем в частное 0 и сносим число
        if (compare_mantissa(dividend, divisor) == FALSE)
        {
            left_shift(&dividend);
            quotient.mantissa[i] = '0';
        }
        // В противном случае просто делим
        else
        {
            digit = count_multiplier(&dividend, divisor);
            quotient.mantissa[i] = '0' + digit;
        }
    }
    quotient.mantissa[MAX_MANTISSA + 1] = '\0';

    // Округление результата
    if ((i == MAX_MANTISSA + 1) && (digit = count_multiplier(&dividend, divisor)) >= 5)
        quotient.mantissa[MAX_MANTISSA] += 1;

    // Приведение мантиссы к 30 знакам
    while (i < MAX_MANTISSA + 1)
    {
        quotient.mantissa[i] = '0';
        i++;
    }
    quotient.mantissa[MAX_MANTISSA + 1] = '\0';

    // Округление высших разрядов (в случае 0.999....)
    int increment = FALSE;
    for (i = MAX_MANTISSA; i >= 0; i--)
    {
        quotient.mantissa[i] += increment;
        // Округление (':' соотвествует переходу через десяток в разряде)
        if (quotient.mantissa[i] == ':')
        {
            quotient.mantissa[i] = '0';
            increment = TRUE;
        }
        else
            break;
    }

    if (quotient.mantissa[0] == '1')
    {
        for (i = MAX_MANTISSA; i > 0; i--)
            quotient.mantissa[i] = quotient.mantissa[i - 1];
        quotient.mantissa[0] = '0';
    }
    else
        increment = FALSE;
    quotient.mantissa[MAX_MANTISSA + 1] = '\0';
    
    if (dividend.sign == divisor.sign)
        quotient.sign = PLUS;
    else
        quotient.sign = MINUS;

    // Считаем разность экспоненты (из-за сдвигов)
    quotient.exponent = dividend.exponent - divisor.exponent + increment + 1;
    return quotient;
}


// Вывод сообщения об ошибке
void print_error(const int code)
{
    if (code == EMPTY_ERROR)
        printf ("Number hasn't been entered!\n");
    if (code == INPUT_ERROR)
        printf("Invalid input, please check the template!\n");
    if (code == LENGTH_LIMIT_ERROR)
        printf("Maximal length of the number has been exceeded!\n");
    if (code == DIVISOR_FORM_ERROR)
        printf("Divisor should be integer!\n");
    if (code == NULL_ERROR)
        printf("Invalid number has been entered!\n");
    if (code == ZERO_DIVISION_ERROR)
        printf("Divisor can't be equal ZERO\n");
    if (code == MANT_LENGTH_ERROR)
        printf("Maximal length of the number's mantissa has been exceeded!\n");
    if (code == EXP_LENGTH_ERROR)
        printf("Maximal length of the number's exponent has been exceeded!\n");
    if (code == EXP_OVERFLOW)
        printf("Number's exponent has been exceeded the grid!\n");
}


// Печать частного
void print_quotient(num_t data)
{
    printf("Quotient = ");
    if (data.sign == '-')
        printf("-");

    int length = strlen(data.mantissa);
    int i;
    for (i = length - 1; (data.mantissa[i] == '0') && (i > 1); i--);
    data.mantissa[i + 1] = '\0';

    printf("0.%s", &data.mantissa[1]);
    printf("e%d\n", data.exponent);
}


int main()
{
    welcome(); // Информация для пользователя

    char input_data[MAX_LENGTH]; // Строка с непроверенными данными, введёнными пользователем.

    num_t dividend, divisor, quotient;
    dividend.sign = PLUS;
    divisor.sign = PLUS;

    // Получение данных от пользователя и проверка корректности.
    //Если пользоввтель ввёл данные не правильно, завершаем работу программы, возвращаем соответсвующий ошибке код,
    // выводим сообщение для информирования пользователя.

    printf("            SCALE          10        20        30        40\n");
    printf("                   ---------|---------|---------|---------|\n");

    printf("Enter the dividend:");
    int input_code = input_number(input_data, DIVIDEND_TYPE);
    if (input_code)
    {
        print_error(input_code);
        return input_code;
    }

    input_code = check_data(input_data);
    if (input_code)
    {
        print_error(input_code);
        return input_code;
    }
    parse_number(input_data, &dividend);

    printf("Enter the divisor: ");
    input_code = input_number(input_data, DIVISOR_TYPE);
    if (input_code)
    {
        print_error(input_code);
        return input_code;
    }

    input_code = check_data(input_data);
    if (input_code)
    {
        print_error(input_code);
        return input_code;
    }
    parse_number(input_data, &divisor);

    quotient = compute_quotient(dividend, divisor);

    // В случае переполнения разрядной сетки экспоненты
    if ((quotient.exponent > MAX_EXP) || (quotient.exponent < MIN_EXP))
    {
        print_error(EXP_OVERFLOW);
        return EXP_OVERFLOW;
    }
    else
        print_quotient(quotient);

    return SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "s21_string.h"
#include <errno.h>


// 1. *****STRLEN*****
s21_size s21_strlen(const char *str) {

    s21_size count = 0;

    while (*str != '\0') {
        count++; 
        str++; 
    }

    return count; 
}

// 2. *****STRCHR*****
char *s21_strchr(const char *str, int value) {

    while (*str != '\0') {

        if (*str == (unsigned char)value) {
            return (char *)str; 
        }

        str++; 
    }

    if (value == '\0') {
        return (char *)str; 
    }

    return S21_NULL; 
}

// 3. *****STRRCHR*****
char *s21_strrchr(const char *str, int value) {

    char *last_char = S21_NULL; 

    while (*str != '\0') {

        if (*str == (unsigned char)value) {
            last_char = (char *)str; 
        }

        str++; 
    }

    if (value == '\0') {
        return (char *)str; 
    }

    return last_char; 
}

// 4. MEMSET
void *s21_memset(void *Dst, int Val, s21_size num) {

    unsigned char *dst = Dst; 
    unsigned char val = Val; 

    for (s21_size i = 0; i < num; i++) {
        dst[i] = val; 
    }

    return Dst; 
}

// 5. MEMCHR
void *s21_memchr(const void *Buff, int Val, s21_size num) {

    const unsigned char *buff = Buff; 
    unsigned char val = Val; 

    for (s21_size i = 0; i < num; i++) {
        if (buff[i] == val) {
            return (void *)&buff[i]; 
        }
    }

    return S21_NULL; 
}

// 6. MEMCMP 
int s21_memcmp(const void *Buff1, const void *Buff2, s21_size num) {

    const unsigned char *buff1 = Buff1; 
    const unsigned char *buff2 = Buff2; 

    for (s21_size i = 0; i < num; i++) {
        if (buff1[i] != buff2[i]) {
            return buff1[i] - buff2[i]; 
        }
    }

    return 0; 
    
}

// 7. MEMCPY
void *s21_memcpy(void *Dst, const void *Src, s21_size num) {

    unsigned char *dst = Dst; 
    const unsigned char *src = Src; 

    for (s21_size i = 0; i < num; i++) {
        dst[i] = src[i];
    }

    return Dst; 
}

// 8. STRNCPY
char *s21_strncpy(char *dst, const char *src, s21_size num) {


    s21_size i = 0; 

    while (i < num && src[i] != '\0') {

        dst[i] = src[i]; 
        i++; 

    }

    while (i < num) {
        dst[i] = '\0'; 
        i++; 
    }

    return dst; 

}

// 9. STRNCAT 
char *s21_strncat(char *dst, const char *src, s21_size num) {

    s21_size i = 0; 
    while (dst[i] != '\0') {
        i++; 
    }

    s21_size a = 0; 
    while (a < num && src[a] != '\0') {
        dst[i] = src[a]; 
        i++; 
        a++; 
    }

    dst[i] = '\0'; 

    return dst; 

}

// 10. STRNCMP
int s21_strncmp(const char *str1, const char *str2, s21_size num) {

    s21_size i = 0; 

    while (i < num) {

        if (str1[i] != str2[i]) {
            return str1[i] - str2[i]; 
        }

        if (str1[i] == '\0') {
            return 0; 
        }

        i++; 
    }

    return 0; 

}


// 11. STRCSPN 
s21_size s21_strcspn(const char *str, const char *set) {

    s21_size count = 0; 
   
    while (str[count] != '\0') {

        s21_size j = 0; 

        while (set[j] != '\0') {

            if (str[count] == set[j]) {
                return count; 
            }
            j++;  
        }

        count++; 

    }

    return count;

}

// 12. STRPBRK
char *s21_strpbrk(const char *str, const char *set) {

    s21_size i = 0; 
    while (str[i] != '\0') {

        s21_size j = 0; 
        while (set[j] != '\0') {
            if (str[i] == set[j]) {
                return (char *)&str[i]; 
            }
            j++; 
        }

        i++; 
    }

    return S21_NULL;  

}

// 13. STRSTR 
char *s21_strstr(const char *haystack, const char *needle) {

    if (needle[0] == '\0') {
        return (char *)haystack; 
    }

     
    for (s21_size i = 0; haystack[i] != '\0'; i++) {

        s21_size j = 0; 
        while (needle[j] != '\0' && needle[j] == haystack[i + j]) {
            j++; 
        }

        if (needle[j] == '\0') {
            return (char *)&haystack[i]; 
        }

    }

    return S21_NULL; 

}

// 14. STRTOK 
char *s21_strtok(char *str, const char *delimiter) {

    static char *saved = S21_NULL; 

    if (str != S21_NULL) {
        saved = str; 
    }

    if (saved == S21_NULL) {
        return S21_NULL; 
    }

    // skip any leading delimiters 
    while (*saved != '\0' && s21_strchr(delimiter, *saved) != S21_NULL) {
        saved++; 
    }

    if (*saved == '\0') {
        saved = S21_NULL; 
        return S21_NULL; 
    }

    char *token = saved; 

    while (*saved != '\0' && s21_strchr(delimiter, *saved) == S21_NULL) {
        saved++; 
    }

    if (*saved == '\0') {
        saved = S21_NULL; 
    } else {
        *saved = '\0'; 
        saved++; 
    }

    return token; 

}

// 15. STRERROR
char *s21_strerror(int errnum) {

static char unknown_message[64]; 

#if defined(__linux__)

    const char *messages[] = {
        [0] = "Success",
        [1] = "Operation not permitted",
        [2] = "No such file or directory",
        [3] = "No such process",
        [4] = "Interrupted system call",
        [5] = "Input/output error",
        [6] = "No such device or address",
        [7] = "Argument list too long",
        [8] = "Exec format error",
        [9] = "Bad file descriptor",
        [10] = "No child processes",
        [11] = "Resource temporarily unavailable",
        [12] = "Cannot allocate memory",
        [13] = "Permission denied",
        [14] = "Bad address",
        [15] = "Block device required",
        [16] = "Device or resource busy",
        [17] = "File exists",
        [18] = "Invalid cross-device link",
        [19] = "No such device",
        [20] = "Not a directory",
        [21] = "Is a directory",
        [22] = "Invalid argument",
        [23] = "Too many open files in system",
        [24] = "Too many open files",
        [25] = "Inappropriate ioctl for device",
        [26] = "Text file busy",
        [27] = "File too large",
        [28] = "No space left on device",
        [29] = "Illegal seek",
        [30] = "Read-only file system",
        [31] = "Too many links",
        [32] = "Broken pipe",
        [33] = "Numerical argument out of domain",
        [34] = "Numerical result out of range",
        [35] = "Resource deadlock avoided",
        [36] = "File name too long",
        [37] = "No locks available",
        [38] = "Function not implemented",
        [39] = "Directory not empty",
        [40] = "Too many levels of symbolic links",
        [42] = "No message of desired type",
        [43] = "Identifier removed",
        [44] = "Channel number out of range",
        [45] = "Level 2 not synchronized",
        [46] = "Level 3 halted",
        [47] = "Level 3 reset",
        [48] = "Link number out of range",
        [49] = "Protocol driver not attached",
        [50] = "No CSI structure available",
        [51] = "Level 2 halted",
        [52] = "Invalid exchange",
        [53] = "Invalid request descriptor",
        [54] = "Exchange full",
        [55] = "No anode",
        [56] = "Invalid request code",
        [57] = "Invalid slot",
        [59] = "Bad font file format",
        [60] = "Device not a stream",
        [61] = "No data available",
        [62] = "Timer expired",
        [63] = "Out of streams resources",
        [64] = "Machine is not on the network",
        [65] = "Package not installed",
        [66] = "Object is remote",
        [67] = "Link has been severed",
        [68] = "Advertise error",
        [69] = "Srmount error",
        [70] = "Communication error on send",
        [71] = "Protocol error",
        [72] = "Multihop attempted",
        [73] = "RFS specific error",
        [74] = "Bad message",
        [75] = "Value too large for defined data type",
        [76] = "Name not unique on network",
        [77] = "File descriptor in bad state",
        [78] = "Remote address changed",
        [79] = "Can not access a needed shared library",
        [80] = "Accessing a corrupted shared library",
        [81] = ".lib section in a.out corrupted",
        [82] = "Attempting to link in too many shared libraries",
        [83] = "Cannot exec a shared library directly",
        [84] = "Invalid or incomplete multibyte or wide character",
        [85] = "Interrupted system call should be restarted",
        [86] = "Streams pipe error",
        [87] = "Too many users",
        [88] = "Socket operation on non-socket",
        [89] = "Destination address required",
        [90] = "Message too long",
        [91] = "Protocol wrong type for socket",
        [92] = "Protocol not available",
        [93] = "Protocol not supported",
        [94] = "Socket type not supported",
        [95] = "Operation not supported",
        [96] = "Protocol family not supported",
        [97] = "Address family not supported by protocol",
        [98] = "Address already in use",
        [99] = "Cannot assign requested address",
        [100] = "Network is down",
        [101] = "Network is unreachable",
        [102] = "Network dropped connection on reset",
        [103] = "Software caused connection abort",
        [104] = "Connection reset by peer",
        [105] = "No buffer space available",
        [106] = "Transport endpoint is already connected",
        [107] = "Transport endpoint is not connected",
        [108] = "Cannot send after transport endpoint shutdown",
        [109] = "Too many references: cannot splice",
        [110] = "Connection timed out",
        [111] = "Connection refused",
        [112] = "Host is down",
        [113] = "No route to host",
        [114] = "Operation already in progress",
        [115] = "Operation now in progress",
        [116] = "Stale file handle",
        [117] = "Structure needs cleaning",
        [118] = "Not a XENIX named type file",
        [119] = "No XENIX semaphores available",
        [120] = "Is a named type file",
        [121] = "Remote I/O error",
        [122] = "Disk quota exceeded",
        [123] = "No medium found",
        [124] = "Wrong medium type",
        [125] = "Operation canceled",
        [126] = "Required key not available",
        [127] = "Key has expired",
        [128] = "Key has been revoked",
        [129] = "Key was rejected by service",
        [130] = "Owner died",
        [131] = "State not recoverable",
        [132] = "Operation not possible due to RF-kill",
        [133] = "Memory page has hardware error"
    };
    
    int length = sizeof(messages) / sizeof(messages[0]); 

#elif defined(__APPLE__) 

    const char *messages[] = {
        [0] = "Undefined error: 0",
        [1] = "Operation not permitted",
        [2] = "No such file or directory",
        [3] = "No such process",
        [4] = "Interrupted system call",
        [5] = "Input/output error",
        [6] = "Device not configured",
        [7] = "Argument list too long",
        [8] = "Exec format error",
        [9] = "Bad file descriptor",
        [10] = "No child processes",
        [11] = "Resource deadlock avoided",
        [12] = "Cannot allocate memory",
        [13] = "Permission denied",
        [14] = "Bad address",
        [15] = "Block device required",
        [16] = "Device / Resource busy",
        [17] = "File exists",
        [18] = "Cross-device link",
        [19] = "Operation not supported by device",
        [20] = "Not a directory",
        [21] = "Is a directory",
        [22] = "Invalid argument",
        [23] = "Too many open files in system",
        [24] = "Too many open files",
        [25] = "Inappropriate ioctl for device",
        [26] = "Text file busy",
        [27] = "File too large",
        [28] = "No space left on device",
        [29] = "Illegal seek",
        [30] = "Read-only file system",
        [31] = "Too many links",
        [32] = "Broken pipe",
        [33] = "Numerical argument out of domain",
        [34] = "Result too large",
        [35] = "Resource temporarily unavailable",
        [36] = "Operation now in progress",
        [37] = "Operation already in progress",
        [38] = "Socket operation on non-socket",
        [39] = "Destination address required",
        [40] = "Message too long",
        [41] = "Protocol wrong type for socket",
        [42] = "Protocol not available",
        [43] = "Protocol not supported",
        [44] = "Socket type not supported",
        [45] = "Operation not supported",
        [46] = "Protocol family not supported",
        [47] = "Address family not supported by protocol family",
        [48] = "Address already in use",
        [49] = "Can't assign requested address",
        [50] = "Network is down",
        [51] = "Network is unreachable",
        [52] = "Network dropped connection on reset",
        [53] = "Software caused connection abort",
        [54] = "Connection reset by peer",
        [55] = "No buffer space available",
        [56] = "Socket is already connected",
        [57] = "Socket is not connected",
        [58] = "Can't send after socket shutdown",
        [59] = "Too many references: can't splice",
        [60] = "Operation timed out",
        [61] = "Connection refused",
        [62] = "Too many levels of symbolic links",
        [63] = "File name too long",
        [64] = "Host is down",
        [65] = "No route to host",
        [66] = "Directory not empty",
        [67] = "Too many processes",
        [68] = "Too many users",
        [69] = "Disc quota exceeded",
        [70] = "Stale NFS file handle",
        [71] = "Too many levels of remote in path",
        [72] = "RPC struct is bad",
        [73] = "RPC version wrong",
        [74] = "RPC prog. not avail",
        [75] = "Program version wrong",
        [76] = "Bad procedure for program",
        [77] = "No locks available",
        [78] = "Function not implemented",
        [79] = "Inappropriate file type or format",
        [80] = "Authentication error",
        [81] = "Need authenticator",
        [82] = "Device power is off",
        [83] = "Device error",
        [84] = "Value too large to be stored in data type",
        [85] = "Bad executable",
        [86] = "Bad CPU type in executable",
        [87] = "Shared library version mismatch",
        [88] = "Malformed Mach-O file",
        [89] = "Operation canceled",
        [90] = "Identifier removed",
        [91] = "No message of desired type",
        [92] = "Illegal byte sequence",
        [93] = "Attribute not found",
        [94] = "Bad message",
        [95] = "Reserved",
        [96] = "No message available on STREAM",
        [97] = "Reserved",
        [98] = "No STREAM resources",
        [99] = "Not a STREAM",
        [100] = "Protocol error",
        [101] = "STREAM ioctl timeout",
        [102] = "Operation not supported on socket",
        [103] = "No such policy registered",
        [104] = "State not recoverable",
        [105] = "Previous owner died",
        [106] = "Interface output queue is full"
    };

    int length = sizeof(messages) / sizeof(messages[0]); 

#else
    #error "Unsupported operating system"
#endif


    if (errnum >= 0 && errnum < length && messages[errnum] != NULL) {
        return (char *)messages[errnum]; 
    }

    snprintf(unknown_message, sizeof(unknown_message), "Unknown error %d", errnum);

    return unknown_message; 
}

// 16. SPRINTF
static void s21_put_char(char **out, int *count, char c) {
    *(*out)++ = c;
    (*count)++;
}

static void s21_put_repeat(char **out, int *count, char c, int n) {
    while (n-- > 0) {
        s21_put_char(out, count, c);
    }
}

static int s21_parse_number(const char **p) {
    int value = 0;

    while (**p >= '0' && **p <= '9') {
        int digit = **p - '0';

        if (value > (INT_MAX - digit) / 10) {
            value = INT_MAX;
        } else {
            value = value * 10 + digit;
        }

        (*p)++;
    }

    return value;
}

static int s21_unsigned_to_string(unsigned long long value,
                                  char *buffer) {
    char reverse[32];
    int len = 0;

    do {
        reverse[len++] = (char)('0' + value % 10);
        value /= 10;
    } while (value != 0);

    for (int i = 0; i < len; i++) {
        buffer[i] = reverse[len - 1 - i];
    }

    buffer[len] = '\0';
    return len;
}

static void s21_emit_field(char **out, int *count,
                           const char *text, int len,
                           char sign, int width, int left,
                           int zero_pad) {
    int total = len + (sign != '\0');
    int padding = width > total ? width - total : 0;

    if (!left && !zero_pad) {
        s21_put_repeat(out, count, ' ', padding);
    }

    if (sign != '\0') {
        s21_put_char(out, count, sign);
    }

    if (!left && zero_pad) {
        s21_put_repeat(out, count, '0', padding);
    }

    for (int i = 0; i < len; i++) {
        s21_put_char(out, count, text[i]);
    }

    if (left) {
        s21_put_repeat(out, count, ' ', padding);
    }
}

static void s21_emit_integer(char **out, int *count,
                             unsigned long long value,
                             char sign, int width, int precision,
                             int precision_set, int left,
                             int zero_flag, int is_zero) {
    char digits[32];
    int len = s21_unsigned_to_string(value, digits);

    if (precision_set && precision == 0 && is_zero) {
        len = 0;
    }

    int zeros = precision_set && precision > len
                    ? precision - len
                    : 0;

    char result[64];
    int result_len = 0;

    while (zeros-- > 0) {
        result[result_len++] = '0';
    }

    for (int i = 0; i < len; i++) {
        result[result_len++] = digits[i];
    }

    result[result_len] = '\0';

    /*
     * Integer precision overrides the zero-padding flag.
     */
    int use_zero_pad = zero_flag && !left && !precision_set;

    s21_emit_field(out, count, result, result_len,
                   sign, width, left, use_zero_pad);
}

static void s21_emit_float(char **out, int *count,
                           double value, char sign,
                           int width, int precision,
                           int left, int zero_flag) {
    /*
     * This implementation uses an integer/fraction split and
     * rounds the fractional part. Extremely large values and
     * extreme precisions are outside this simple implementation's
     * safe range.
     */
    if (precision < 0) {
        precision = 6;
    }

    if (precision > 18) {
        precision = 18;
    }

    if (value < 0.0) {
        sign = '-';
        value = -value;
    }

    unsigned long long whole = (unsigned long long)value;
    long double fraction = (long double)value - (long double)whole;

    unsigned long long scale = 1;
    for (int i = 0; i < precision; i++) {
        scale *= 10;
    }

    unsigned long long fractional =
    (unsigned long long)(fraction * (long double)scale + 0.5L);

    if (fractional >= scale) {
    whole++;
    fractional -= scale;
    }

    char whole_text[32];
    int whole_len = s21_unsigned_to_string(whole, whole_text);

    char result[64];
    int result_len = 0;

    for (int i = 0; i < whole_len; i++) {
        result[result_len++] = whole_text[i];
    }

    if (precision > 0) {
        result[result_len++] = '.';

        unsigned long long divisor = scale / 10;
        for (int i = 0; i < precision; i++) {
            result[result_len++] =
                (char)('0' + (fractional / divisor) % 10);

            if (divisor > 1) {
                divisor /= 10;
            }
        }
    }

    result[result_len] = '\0';

    s21_emit_field(out, count, result, result_len,
                   sign, width, left, zero_flag && !left);
}

int s21_sprintf(char *str, const char *format, ...) {
    if (str == NULL || format == NULL) {
        return -1;
    }

    char *out = str;
    int count = 0;

    va_list args;
    va_start(args, format);

    const char *p = format;

    while (*p != '\0') {
        if (*p != '%') {
            s21_put_char(&out, &count, *p++);
            continue;
        }

        p++;

        if (*p == '%') {
            s21_put_char(&out, &count, '%');
            p++;
            continue;
        }

        int left = 0;
        int plus = 0;
        int space = 0;
        int zero_flag = 0;

        /* Flags */
        int parsing_flags = 1;
        while (parsing_flags) {
            switch (*p) {
                case '-': left = 1; p++; break;
                case '+': plus = 1; p++; break;
                case ' ': space = 1; p++; break;
                case '0': zero_flag = 1; p++; break;
                default: parsing_flags = 0; break;
            }
        }

        /* Numeric width */
        int width = 0;
        if (*p >= '0' && *p <= '9') {
            width = s21_parse_number(&p);
        }

        /* Numeric precision */
        int precision = 0;
        int precision_set = 0;

        if (*p == '.') {
            precision_set = 1;
            p++;

            if (*p >= '0' && *p <= '9') {
                precision = s21_parse_number(&p);
            }
        }

        /* Length modifier */
        char length = '\0';
        if (*p == 'h' || *p == 'l') {
            length = *p;
            p++;
        }

        char conversion = *p;
        if (conversion == '\0') {
            break;
        }
        p++;

        char sign = '\0';
        if (plus) {
            sign = '+';
        } else if (space) {
            sign = ' ';
        }

        switch (conversion) {
            case 'c': {
                char c = (char)va_arg(args, int);
                int padding = width > 1 ? width - 1 : 0;

                if (!left) {
                    s21_put_repeat(&out, &count, ' ', padding);
                }

                s21_put_char(&out, &count, c);

                if (left) {
                    s21_put_repeat(&out, &count, ' ', padding);
                }
                break;
            }

            case 's': {
                const char *value = va_arg(args, const char *);
                if (value == NULL) {
                    value = "(null)";
                }

                int len = 0;
                while (value[len] != '\0' &&
                       (!precision_set || len < precision)) {
                    len++;
                }

                s21_emit_field(&out, &count, value, len,
                               '\0', width, left, 0);
                break;
            }

            case 'd': {
                long long value;

                if (length == 'l') {
                    value = va_arg(args, long);
                } else if (length == 'h') {
                    value = (short)va_arg(args, int);
                } else {
                    value = va_arg(args, int);
                }

                unsigned long long magnitude;
                if (value < 0) {
                    sign = '-';
                    magnitude = (unsigned long long)(-(value + 1)) + 1;
                } else {
                    magnitude = (unsigned long long)value;
                }

                s21_emit_integer(&out, &count, magnitude, sign,
                                 width, precision, precision_set,
                                 left, zero_flag, magnitude == 0);
                break;
            }

            case 'u': {
                unsigned long long value;

                if (length == 'l') {
                    value = va_arg(args, unsigned long);
                } else if (length == 'h') {
                    value = (unsigned short)va_arg(args, int);
                } else {
                    value = va_arg(args, unsigned int);
                }

                s21_emit_integer(&out, &count, value, '\0',
                                 width, precision, precision_set,
                                 left, zero_flag, value == 0);
                break;
            }

            case 'f': {
                double value = va_arg(args, double);

                if (value < 0.0) {
                    sign = '-';
                }

                s21_emit_float(&out, &count, value, sign,
                               width,
                               precision_set ? precision : 6,
                               left, zero_flag);
                break;
            }

            default:
                /* Unknown conversion: preserve the format text. */
                s21_put_char(&out, &count, '%');
                s21_put_char(&out, &count, conversion);
                break;
        }
    }

    *out = '\0';
    va_end(args);

    return count;
}

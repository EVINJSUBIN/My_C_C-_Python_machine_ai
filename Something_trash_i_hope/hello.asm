section .data
    msg db 'HTTP/1.1 200 OK', 0x0D, 0x0A
    msg2 db 'Content-Type: text/html', 0x0D, 0x0A
    msg3 db 'Content-Length: 13', 0x0D, 0x0A, 0x0D, 0x0A
    msg4 db 'Hello World!', 0x0D, 0x0A
    msg_len equ $ - msg

section .bss
    buffer resb 1024

section .text
    global _start

_start:
    ; Create socket (syscall: socket)
    mov rax, 41         ; syscall number for socket
    xor rdi, rdi        ; AF_INET (IPv4)
    mov rdi, 2          ; SOCK_STREAM (TCP)
    xor rdx, rdx        ; IPPROTO_IP (default)
    syscall

    ; Store the socket file descriptor
    mov rdi, rax        ; rdi will hold the socket file descriptor

    ; Bind socket (syscall: bind)
    mov rax, 49         ; syscall number for bind
    mov rsi, rsp        ; pointer to sockaddr struct (we’ll define it on stack)
    push word 0x0B13    ; Port 8080 (in network byte order)
    push word 0x0002    ; AF_INET
    push dword 0x00000000  ; INADDR_ANY (all interfaces)
    mov rdx, 16         ; Length of sockaddr_in struct (16 bytes)
    syscall

    ; Listen (syscall: listen)
    mov rax, 50         ; syscall number for listen
    xor rsi, rsi        ; backlog: number of connections (default 0)
    syscall

    ; Accept connection (syscall: accept)
    mov rax, 43         ; syscall number for accept
    mov rdx, 0          ; NULL (no sockaddr storage)
    mov rsi, 0          ; NULL (no length storage)
    syscall

    ; Read HTTP request (syscall: read)
    mov rdi, rax        ; use the file descriptor returned by accept
    mov rax, 0          ; syscall number for read
    mov rsi, buffer     ; buffer to store the request
    mov rdx, 1024       ; read up to 1024 bytes
    syscall

    ; Send HTTP response (syscall: write)
    mov rax, 1          ; syscall number for write
    mov rsi, msg        ; point to the response message
    mov rdx, msg_len    ; length of the response
    syscall

    ; Exit (syscall: exit)
    mov rax, 60         ; syscall number for exit
    xor rdi, rdi        ; exit code 0
    syscall

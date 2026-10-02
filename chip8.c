#include <stdio.h>



#define PC_START 0x200
#define I_START 0
#define OPCODE_START 0
#define SP_START 0
#define FONTSET_SIZE 80


typedef struct{
uint8_t ram[4096];
uint8_t V[16];
uint16_t I;
uint16_t pc;

uint16_t stack[16];
uint8_t sp;

uint8_t delay_timer;
uint8_t sound_timer;

uint32_t gfx[64 * 32];
uint8_t key[16]

uint16_t opcode;
;

} Chip8;


uint8_t chip8_fontset[FONTSET_SIZE] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


void load_rom(Chip8 *chip8, const char *filename) {

    FILE *rom = fopen(filename, "rb");
    

    if(rom) {
        

        // Find ROM file size by going to the end, knowing where it is, then
        fseek(rom,0,SEEK_END);
        long size = ftell(rom);
        long max_size = sizeof chip8->ram - PC_START;
        fseek(rom,0,SEEK_SET);

       // fread(&chip8->ram[PC_START], size, 1, rom)

        if (size > max_size){
            fprintf(stderr, "ROM is too big!");
            return
        }

        for(int i = 0; i < size; i++){
            int b = fgetc(rom);
            if (b == EOF) {
                fprintf(stderr, "File is empty!");
               return;
            }
            chip8->ram[PC_START + i] = b; 
        }

        fclose(rom);

        return;
    }

    fprintf(stderr, "ROM is invalid!");

}

void initialize(Chip8 *chip8){
    chip8->pc = PC_START;
    chip8->I = I_START;
    chip8->sp = SP_START;
    chip8->opcode = OPCODE_START;

    for (int i = 0; i < FONTSET_SIZE; i++){
        chip8->ram[i] = chip8_fontset[i];
    }


void update_timers(Chip8 *chip8){
    if (delay_timer > 0) {
        delay_timer--;
    }

    if (sound_timer > 0) {
        sound_timer--;
    }
}



}
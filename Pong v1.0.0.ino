#include <TVout.h>
#include <video_gen.h>
#include <fontALL.h>

#define LARGURA_TELA 120
#define ALTURA_TELA 96
#define LIMITE_SUP 9
#define LIMITE_INF 86

TVout TV;

int velocidadeJogo = 25;
int velocidadeBolaX = 1;
int velocidadeBolaY = -1;
int entradaJoystickPlayer1 = A0;
int entradaJoystickPlayer2 = A1;
boolean startGame = false;
boolean donoDaBola = true;
int posicaoPlayer1X = 5;
int posicaoPlayer1Y;
int posicaoPlayer2X = 114;
int posicaoPlayer2Y;
int sentidoPlayer1;
int sentidoPlayer2;
int posicaoBolaX = 7;
int posicaoBolaY;
int pontosPlayer1 = 0;
int pontosPlayer2 = 0;
int play = 2;
int tonePin = 11;

void setup() {
    pinMode (play,INPUT);
    TV.begin(_PAL, LARGURA_TELA, ALTURA_TELA);
    posicaoPlayer1Y = map(analogRead(entradaJoystickPlayer1), 0, 1023, 16, 79);
    posicaoPlayer2Y = map(analogRead(entradaJoystickPlayer2), 0, 1023, 16, 79);
    sentidoPlayer1 = posicaoPlayer1Y;
    sentidoPlayer2 = posicaoPlayer2Y;
    posicaoBolaY = posicaoPlayer1Y;
}

void loop() {
    int estado = digitalRead (play);
    
    if (estado == 0) {
      TV.clear_screen();
      TV.select_font(font6x8);
      TV.print(44, 0, pontosPlayer1);
      TV.print(70, 0, pontosPlayer2);
      TV.select_font(font4x6);
      TV.print(42, 90, "Ping Pong");
      desenhaCenario();
      verificaMovimentoPlayers();
      movimentaBola();
      delay(velocidadeJogo);
      if(pontosPlayer1 == 6) {
        gameOver(1);
      } else if(pontosPlayer2 == 6) {
          gameOver(2);
      }
    }else{
       TV.clear_screen();
    TV.select_font(font6x8);
    TV.print(44, 0, pontosPlayer1);
    TV.print(70, 0, pontosPlayer2);
    TV.select_font(font4x6);
    TV.print(42, 90, " Fronton ");
    desenhaCenario2();
    verificaMovimentoPlayers2();
    movimentaBola2();
    delay(velocidadeJogo);
    if(pontosPlayer1 == 50) {
        gameOver2(1);
    } else if(pontosPlayer2 == 6) {
        gameOver2(2);
    }
      }
 }

void desenhaCenario() {
    TV.draw_rect(0, 8, LARGURA_TELA - 1, ALTURA_TELA - 17, WHITE);
    for(int i = 9; i <= 85; i = i + 5) {
        TV.draw_column((LARGURA_TELA / 2) - 1, i, i + 2, WHITE);
    }
    TV.draw_column(posicaoPlayer1X, (posicaoPlayer1Y - 7), (posicaoPlayer1Y + 7), WHITE);
    TV.draw_column(posicaoPlayer2X, (posicaoPlayer2Y - 7), (posicaoPlayer2Y + 7), WHITE);
    TV.set_pixel(posicaoBolaX, posicaoBolaY, WHITE);
}

void desenhaCenario2 () {
    TV.draw_rect(0, 8, LARGURA_TELA - 1, ALTURA_TELA - 17, WHITE);
    for(int i = 9; i <= 85; i = i + 5) {
        TV.draw_column((LARGURA_TELA / 2) - 1, i, i + 2, WHITE);
    }
    TV.draw_column(posicaoPlayer1X, (posicaoPlayer1Y - 7), (posicaoPlayer1Y + 7), WHITE);
    TV.draw_column(posicaoPlayer2X, (posicaoPlayer2Y - 7), (posicaoPlayer2Y + 7), BLACK);
    TV.set_pixel(posicaoBolaX, posicaoBolaY, WHITE);
}


void verificaMovimentoPlayers() {
    posicaoPlayer1Y = map(analogRead(entradaJoystickPlayer1), 0, 1023, 16, 79);
    if(sentidoPlayer1 < posicaoPlayer1Y) {
        if(!startGame && donoDaBola) {
            velocidadeBolaY = 1;
            startGame = true;
        }        
    } else if(sentidoPlayer1 > posicaoPlayer1Y) {
        if(!startGame && donoDaBola) {
            velocidadeBolaY = -1;
            startGame = true;
        }        
    }

    posicaoPlayer2Y = map(analogRead(entradaJoystickPlayer2), 0, 1023, 16, 79);
    if(sentidoPlayer2 < posicaoPlayer2Y) {
        if(!startGame && !donoDaBola) {
            velocidadeBolaY = 1;
            startGame = true;
        }
    } else if(sentidoPlayer2 > posicaoPlayer2Y) {
        if(!startGame && !donoDaBola) {
            velocidadeBolaY = -1;
            startGame = true;
        }
    }
    sentidoPlayer1 = posicaoPlayer1Y;
    sentidoPlayer2 = posicaoPlayer2Y;
}

void verificaMovimentoPlayers2() {
    posicaoPlayer1Y = map(analogRead(entradaJoystickPlayer1), 0, 1023, 16, 79);
    if(sentidoPlayer1 < posicaoPlayer1Y) {
        if(!startGame && donoDaBola) {
            velocidadeBolaY = 1;
            startGame = true;
        }        
    } else if(sentidoPlayer1 > posicaoPlayer1Y) {
        if(!startGame && donoDaBola) {
            velocidadeBolaY = -1;
            startGame = true;
        }        
    }
    posicaoPlayer2Y = map(analogRead(entradaJoystickPlayer1), 0, 1023, 16, 79);
    if(sentidoPlayer2 < posicaoPlayer2Y) {
        if(!startGame && !donoDaBola) {
            velocidadeBolaY = 1;
            startGame = true;
        }
    } else if(sentidoPlayer2 > posicaoPlayer2Y) {
        if(!startGame && !donoDaBola) {
            velocidadeBolaY = -1;
            startGame = true;
        }
    }
    sentidoPlayer1 = posicaoPlayer1Y;
    sentidoPlayer2 = posicaoPlayer2Y;
}

void movimentaBola() {
    int bolaX = posicaoBolaX;
    int bolaY = posicaoBolaY;
    if(startGame) {
        bolaX = posicaoBolaX + velocidadeBolaX;
        bolaY = posicaoBolaY + velocidadeBolaY;      
    }
    if(bolaY == LIMITE_SUP) {
        velocidadeBolaY = 1;
        sonsDoJogo(440, 20);
    }
    else if(bolaY == LIMITE_INF) {
        velocidadeBolaY = -1;
        sonsDoJogo(440, 20); 
    }
    if(bolaX == 7) {
        if(posicaoBolaY < posicaoPlayer1Y + 8 && posicaoBolaY > posicaoPlayer1Y - 8) {
            velocidadeBolaX = 1;            
            if(startGame) {
                sonsDoJogo(220, 20); 
            }            
        }
    }else if(bolaX == 0) {
        startGame = false;
        donoDaBola = false;
        bolaX = 112;
        bolaY = posicaoPlayer2Y;
        pontosPlayer2++;
        sonsDoJogo(100, 300); 
    }
    if(bolaX == 112) {
        if(posicaoBolaY < posicaoPlayer2Y + 8 && posicaoBolaY > posicaoPlayer2Y - 8) {
            velocidadeBolaX = -1;
            if(startGame) {
                sonsDoJogo(220, 20); 
            }            
        }
    }else if(bolaX == LARGURA_TELA) {
        startGame = false;
        donoDaBola = true;
        bolaX = 7;
        bolaY = posicaoPlayer1Y;
        pontosPlayer1++;
        sonsDoJogo(100, 300); 
    }
    posicaoBolaX = bolaX;
    posicaoBolaY = bolaY;
}

void movimentaBola2() {
    int bolaX = posicaoBolaX;
    int bolaY = posicaoBolaY;
    if(startGame) {
        bolaX = posicaoBolaX + velocidadeBolaX;
        bolaY = posicaoBolaY + velocidadeBolaY;      
    }
    if(bolaY == LIMITE_SUP) {
        velocidadeBolaY = 1;
        sonsDoJogo(440, 20); 
    }
    else if(bolaY == LIMITE_INF) {
        velocidadeBolaY = -1;
        sonsDoJogo(440, 20); 
    }
    if(bolaX == 7) {
        if(posicaoBolaY < posicaoPlayer1Y + 8 && posicaoBolaY > posicaoPlayer1Y - 8) {
            velocidadeBolaX = 1;
                  
            if(startGame) {
                
                pontosPlayer1++;
                sonsDoJogo(220, 20); 
            }            
        }
    }else if(bolaX == 0) {
        startGame = false;
        donoDaBola = false;
        bolaX = 7;
        bolaY = posicaoPlayer1Y;
        pontosPlayer2++;
        sonsDoJogo(100, 300); 
    }
    if(bolaX == 59) {
        velocidadeBolaX = -1;
            if(startGame) {
                sonsDoJogo(220, 20); 
            }            
    }
    posicaoBolaX = bolaX;
    posicaoBolaY = bolaY;
}

void sonsDoJogo(int frequencia, int duracao) {
    TV.tone(frequencia, duracao);
}

void gameOver(int vencedor) {
    startGame = false;
    pontosPlayer1 = 0;
    pontosPlayer2 = 0;
    TV.clear_screen();
    TV.select_font(font8x8);
    sonsDoJogo(520, 500); 
    if(vencedor == 1) {
        TV.println(27, 40, "Vencedor");
        TV.println(27, 50, "PLAYER 1");
        donoDaBola = true;
        delay(100000);
    }else if(vencedor == 2) {
        TV.println(27, 40, "Vencedor");
        TV.println(27, 50, "PLAYER 2");
        donoDaBola = false;
        delay(100000);
    }
    midi();
    TV.select_font(font4x6);
    TV.print(20, 90, "Ping Pong by Carlos");
    delay(400000);
}

void gameOver2(int vencedor) {
    startGame = false;
    TV.clear_screen();
    TV.select_font(font8x8);
    sonsDoJogo(520, 500); 
    if(vencedor == 1) {
        TV.println(27, 40, "Descansa");
        TV.println(27, 50, "PLAYER 1");
        TV.println(27, 65, pontosPlayer1);
        TV.println(45, 65, "golpes");
        donoDaBola = true;
        delay(100000);
    }else if(vencedor == 2) {
        TV.println(27, 40, "Vuelbe a");
        TV.println(20, 50, "Intentarlo");
        donoDaBola = false;
        delay(100000);
    }
    pontosPlayer1 = 0;
    pontosPlayer2 = 0;
    midi();
    TV.select_font(font4x6);
    TV.print(20, 90, "Fronton   by  Carlos");
    delay(400000);    
}

void midi() {
    sonsDoJogo(155, 11041.6666667);
    delay(22083.3333333);
    delay(18750.0);
    sonsDoJogo(233, 9583.33333333);
    delay(19166.6666667);
    delay(20416.6666667);
    sonsDoJogo(233, 9583.33333333);
    delay(19166.6666667);
    delay(20416.6666667);
    sonsDoJogo(184, 9583.33333333);
    delay(19166.6666667);
    delay(22083.3333333);
    sonsDoJogo(174, 9375.0);
    delay(18750.0);
    delay(20833.3333333);
    sonsDoJogo(174, 10208.3333333);
    delay(20416.6666667);
    delay(18750.0);
    sonsDoJogo(174, 9583.33333333);
    delay(19166.6666667);
    delay(20416.6666667);
    sonsDoJogo(174, 10416.6666667);
    delay(20833.3333333);
    delay(416.666666667);
    sonsDoJogo(184, 8958.33333333);
    delay(17916.6666667);
    delay(2083.33333333);
    sonsDoJogo(155, 10208.3333333);
    delay(20416.6666667);
    delay(19166.6666667);
    sonsDoJogo(233, 10208.3333333);
    delay(20416.6666667);
    delay(20416.6666667);
    sonsDoJogo(233, 9583.33333333);
    delay(19166.6666667);
    delay(20416.6666667);
    sonsDoJogo(184, 9583.33333333);
    delay(19166.6666667);
    delay(20416.6666667);
    sonsDoJogo(174, 9375.0);
    delay(18750.0);
    delay(20833.3333333);
    sonsDoJogo(174, 9375.0);
    delay(18750.0);
    delay(22083.3333333);
    sonsDoJogo(174, 9583.33333333);
    delay(19166.6666667);
    delay(20416.6666667);
    sonsDoJogo(174, 9583.33333333);
    delay(19166.6666667);
    delay(833.333333333);
    delay(19583.3333333);
    sonsDoJogo(184, 625.0);
    delay(1250.0);
    sonsDoJogo(155, 9791.66666667);
    delay(19583.3333333);
    delay(18750.0);
    sonsDoJogo(233, 9375.0);
    delay(18750.0);
    delay(22500.0);
    sonsDoJogo(233, 9375.0);
    delay(18750.0);
    delay(20416.6666667);
    sonsDoJogo(184, 10416.6666667);
    delay(20833.3333333);
    delay(20416.6666667);
    sonsDoJogo(174, 10416.6666667);
    delay(20833.3333333);
    delay(18750.0);
    sonsDoJogo(174, 9375.0);
    delay(18750.0);
    delay(20833.3333333);
    sonsDoJogo(174, 9375.0);
    delay(18750.0);
    delay(22083.3333333);
    sonsDoJogo(174, 8958.33333333);
    delay(17916.6666667);
    delay(2083.33333333);
    sonsDoJogo(184, 9583.33333333);
    delay(19166.6666667);
    delay(416.666666667);
    sonsDoJogo(155, 8750.0);
    delay(17500.0);
    delay(22083.3333333);
    sonsDoJogo(233, 8541.66666667);
    delay(17083.3333333);
    delay(20833.3333333);
    sonsDoJogo(233, 10208.3333333);
    delay(20416.6666667);
    delay(20416.6666667);
    sonsDoJogo(184, 9583.33333333);
    delay(19166.6666667);
    delay(21666.6666667);
    sonsDoJogo(277, 8541.66666667);
    delay(17083.3333333);
    delay(22916.6666667);
    sonsDoJogo(277, 8541.66666667);
    delay(17083.3333333);
    delay(22916.6666667);
    sonsDoJogo(207, 8541.66666667);
    delay(17083.3333333);
    delay(22916.6666667);
    sonsDoJogo(293, 8541.66666667);
    delay(17083.3333333);
    delay(2916.66666667);
    sonsDoJogo(261, 213.541666667);
    delay(427.083333333);
}    

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct Equipo {
    char nombre[50];
    int partidos_jugados;
    int partidos_ganados;
    int partidos_empatados;
    int partidos_perdidos;
    int puntos;
};

const int kMaxEquipos = 20;
Equipo equipos[kMaxEquipos];
int total_equipos = 16;

bool EsConsistente(Equipo e) {
    bool puntos_ok = (e.puntos == (3 * e.partidos_ganados) + (1 * e.partidos_empatados));
    bool jugados_ok = (e.partidos_jugados == e.partidos_ganados + e.partidos_empatados + e.partidos_perdidos);
    return puntos_ok && jugados_ok;
}

void ReconstruirDatosIniciales() {
    for (int i = 0; i < total_equipos; ++i) {
        equipos[i].partidos_empatados = equipos[i].puntos - (3 * equipos[i].partidos_ganados);
        equipos[i].partidos_perdidos = equipos[i].partidos_jugados - equipos[i].partidos_ganados - equipos[i].partidos_empatados;
    }
}

void ImprimirCabecera() {
    printf("\n%-25s | %-3s | %-3s | %-3s | %-3s | %-6s\n",
        "EQUIPO", "PJ", "PG", "PE", "PP", "PTS");
    printf("\n");
}

void MostrarEquipo(Equipo e) {
    printf("%-25s | %3d | %3d | %3d | %3d | %6d\n",
        e.nombre, e.partidos_jugados, e.partidos_ganados,
        e.partidos_empatados, e.partidos_perdidos, e.puntos);
}


void MostrarTabla(bool descendente) {
    for (int i = 0; i < total_equipos - 1; ++i) {
        for (int j = 0; j < total_equipos - i - 1; ++j) {
            bool condicion = descendente ? (equipos[j].puntos < equipos[j + 1].puntos)
                : (equipos[j].puntos > equipos[j + 1].puntos);
            if (condicion) {
                Equipo temp = equipos[j];
                equipos[j] = equipos[j + 1];
                equipos[j + 1] = temp;
            }
        }
    }

    printf("\nTABLA DE POSICIONES (%s)\n", descendente ? "MAYOR A MENOR" : "MENOR A MAYOR");
    ImprimirCabecera();
    for (int i = 0; i < total_equipos; ++i) {
        MostrarEquipo(equipos[i]);
    }
}

void MostrarMasEmpatado() {
    int max_empates = -1;
    int indice_max = 0;

    for (int i = 0; i < total_equipos; ++i) {
        if (equipos[i].partidos_empatados > max_empates) {
            max_empates = equipos[i].partidos_empatados;
            indice_max = i;
        }
    }

    printf("\nEl equipo con mas empates es: %s (%d empates)\n",
        equipos[indice_max].nombre, equipos[indice_max].partidos_empatados);
}

void BuscarEquipo() {
    char busqueda[50];
    printf("\nIngrese el nombre del equipo a buscar: ");
    scanf(" %[^\n]", busqueda);

    bool encontrado = false;
    for (int i = 0; i < total_equipos; ++i) {
        if (strcmp(equipos[i].nombre, busqueda) == 0) {
            ImprimirCabecera();
            MostrarEquipo(equipos[i]);
            encontrado = true;
            break;
        }
    }
    if (!encontrado) printf("Equipo no encontrado.\n");
}

void AgregarNuevoEquipo() {
    if (total_equipos >= kMaxEquipos) {
        printf("\nError: No se pueden agregar mas de 4 equipos nuevos.\n");
        return;
    }

    Equipo nuevo;
    printf("\n AGREGAR NUEVO EQUIPO \n");
    printf("Nombre: "); scanf(" %[^\n]", nuevo.nombre);
    printf("PJ: "); scanf("%d", &nuevo.partidos_jugados);
    printf("PG: "); scanf("%d", &nuevo.partidos_ganados);
    printf("PE: "); scanf("%d", &nuevo.partidos_empatados);
    printf("PP: "); scanf("%d", &nuevo.partidos_perdidos);
    printf("PTS: "); scanf("%d", &nuevo.puntos);

    if (EsConsistente(nuevo)) {
        equipos[total_equipos] = nuevo;
        total_equipos++;
        printf("¡Equipo agregado exitosamente!\n");
    }
    else {
        printf("\n[ADVERTENCIA]: Los datos no son consistentes.\n");
        printf("- Puntos deben ser (3*PG + 1*PE)\n");
        printf("- PJ debe ser (PG + PE + PP)\n");
        printf("El equipo NO fue guardado.\n");
    }
}

void CargarDatosBase() {
    Equipo iniciales[16] = {
      {"Andromeda FC",12,4,0,0,13}, {"Vulcano Academia",11,2,0,0,10},
      {"Orion Confederacion",11,4,0,0,14}, {"Sirio Estrellas",10,6,0,0,20},
      {"Caronte Titanes",11,1,0,0,6}, {"Quiron Cometas",10,5,0,0,17},
      {"Pegaso Pulsares",11,7,0,0,24}, {"Osos Cosmicos",11,5,0,0,18},
      {"Via Lactea Nomadas",11,6,0,0,20}, {"Leonidas FC",11,5,0,0,16},
      {"Cangrejo Fortaleza",11,4,0,0,16}, {"Cefeo Cumulo",11,3,0,0,14},
      {"Atletico Interestelar",11,4,0,0,16}, {"Deportivo Galactico",11,2,0,0,8},
      {"Estrella Estelar",11,5,0,0,17}, {"Inter Galaxia",10,2,0,0,10}
    };
    for (int i = 0; i < 16; ++i) equipos[i] = iniciales[i];
    ReconstruirDatosIniciales();
}

int main() {
    CargarDatosBase();
    int opcion;

    do {
        printf("\n TORNEO INTERGALACTICO \n");
        printf("1. Tabla Posiciones (Mayor a Menor)\n");
        printf("2. Tabla Posiciones (Menor a Mayor)\n");
        printf("3. Equipo con mas empates\n");
        printf("4. Buscar informacion de equipo\n");
        printf("5. Agregar nuevo equipo\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1: MostrarTabla(true); break;
        case 2: MostrarTabla(false); break;
        case 3: MostrarMasEmpatado(); break;
        case 4: BuscarEquipo(); break;
        case 5: AgregarNuevoEquipo(); break;
        case 6: printf("Saliendo del sistema...\n"); break;
        default: printf("Opcion invalida.\n");
        }
    } while (opcion != 6);

    return 0;
}
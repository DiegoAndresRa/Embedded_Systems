from PIL import (
    ImageColor,
)  # Importa el módulo ImageColor de PIL para trabajar con colores
import matplotlib.pyplot as plt  # Importa matplotlib para crear gráficos
import numpy as np  # Importa numpy para trabajar con arrays y operaciones matemáticas
import random  # Importa random para generar valores aleatorios (aunque no se usa en este código)
import sys  # Importa sys para trabajar con argumentos del sistema
import os  # Importa os para interactuar con el sistema de archivos


def read_data(file):
    # Lee el archivo y convierte las líneas en enteros, ignorando líneas vacías
    with open(file, "r") as f:
        data = [int(linea.strip()) for linea in f if linea.strip()]
    return data  # Devuelve la lista de datos


def generate_hist(datasets, name_of_img, bins=20):
    # Diccionario de colores para los histogramas y curvas
    colors = {
        "blue": "turquoise",
        "green": "yellowgreen",
        "deeppink": "fuchsia",
        "red": "lightcoral",
        "gold": "goldenrod",
    }
    keys = list(colors.keys())  # Lista de claves de los colores
    plt.figure(figsize=(10, 6))  # Crea una figura con tamaño 10x6

    for idx, data in enumerate(datasets):
        # Graficar el histograma para cada conjunto de datos
        plt.hist(
            datasets[data],  # Datos a graficar
            bins=bins,  # Número de bins
            color=colors[keys[idx % len(colors)]],  # Color del histograma
            edgecolor="black",  # Color del borde
            density=True,  # Normaliza el histograma
            alpha=0.6,  # Transparencia
            label=data,  # Etiqueta para la leyenda
        )

        # Calcular media y desviación estándar
        mu, std = np.mean(datasets[data]), np.std(datasets[data])
        # Generar puntos para la curva Gaussiana
        x = np.linspace(min(datasets[data]) - 1, max(datasets[data]) + 1, 100)
        p = (1 / (std * np.sqrt(2 * np.pi))) * np.exp(-0.5 * ((x - mu) / std) ** 2)

        # Graficar la curva de Gauss
        plt.plot(x, p, color=keys[idx % len(colors)], linewidth=3)  # Curva de Gauss

    plt.title("Histograms and Gauss")  # Título del gráfico
    plt.xlabel("Nanoseconds")  # Etiqueta del eje X
    plt.ylabel("Frequency")  # Etiqueta del eje Y
    plt.legend()  # Mostrar la leyenda

    # Descomentar las siguientes líneas para limitar los ejes X e Y
    # plt.xlim(101000000, 104500000)
    # plt.ylim(0, 0.0000075)

    # Formateo de etiquetas en el eje X y Y
    plt.ticklabel_format(style="scientific", axis="x", scilimits=(0, 0))
    plt.ticklabel_format(style="plain", axis="y")

    # Guardar la imagen del histograma
    plt.savefig(f"Histograms/Histogram{name_of_img}.png", format="png")
    plt.close()  # Cierra la figura


if __name__ == "__main__":
    # Comprobar si se han pasado argumentos al script
    if len(sys.argv) == 1:
        sys.exit(
            f"Error:\nUsage: {sys.argv[0]} data_file1 [data_file2 ... ]"
        )  # Error si no hay argumentos
    elif len(sys.argv) == 2:
        name_of_img = os.path.basename(sys.argv[1]).split(".")[
            0
        ]  # Nombre de la imagen basado en el archivo
    else:
        name_of_img = ""  # Nombre vacío si hay más de un archivo

    os.makedirs(
        "Histograms", exist_ok=True
    )  # Crea el directorio "Histograms" si no existe
    datasets = {}  # Diccionario para almacenar los datos

    # Leer cada archivo pasado como argumento
    for arg in sys.argv[1:]:
        data = read_data(arg)  # Leer los datos del archivo
        name = os.path.basename(arg).split(".")[0]  # Extraer el nombre del archivo
        datasets[name] = data  # Guardar los datos en el diccionario

    # Generar el histograma
    generate_hist(datasets, name_of_img, bins=20)

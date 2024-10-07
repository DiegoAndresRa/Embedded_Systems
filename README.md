<div >
  <img src='https://academy.nit-institute.com/wp-content/uploads/2022/05/Embedded.png' height='80'>
  <img src='https://cdn0.iconfinder.com/data/icons/flat-round-system/512/raspberry-512.png' height='80'>
</div>

<h1>Embedded_Systems</h1>

### Descripción
A solution is implemented to capture both the output of the analog-to-digital converter and the hardware execution time for the task. This data is then stored in files for subsequent performance analysis.

The performance analysis is visualized using a histogram of the execution times. However, these histograms don't represent the raw times directly from the solution's output. Instead, they depict the differences between consecutive raw times.


### Methodology
```
Run the solution for each language
    Calculate the time differences between consecutive measurements.
    Generate a histogram to visualize the distribution of execution times.
```

### Utilities

* ```getDifferences.sh```

  **Usage:**

  ```
  NAME
      getDifferences.sh - calculate time differences in nanoseconds
  SYNOPSIS
       getDifferences.sh readFile writeFile
  DESCRIPTION
      The time differences are calculated line by line until the
      entire file is read.
  ```

* ```invert.sh```

  **Usage:**

  ```
  NAME
      invert.sh - reverse the order of the lines in the file
  SYNOPSIS
      invert.sh file
  DESCRIPTION
      This bash script was developed to handle the output of
      the solution developed in C.
  ```

* ```histograms.py```

  **Usage:**

  ```
  NAME
      histograms.py - generates the histogram based on the input data
  SYNOPSIS
       histograms.py file1 [ file2 ... ]
  DESCRIPTION
      Generates the histogram of the input
      data and in addition projects its Gaussian bell curve
  ```

  ### Example of use

  ```bash
  $ python3 Python/codigo.py
  $ ./getDifferences.sh Python/times.txt differences.txt
  $ python3 histograms.py differences.txt
  ```


> [!NOTE]
> The above codes are only designed to run on a Raspberry Pi 3 Model B+

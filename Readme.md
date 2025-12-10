# Registro de Horas Freelance (C++ - Terminal)

Aplicación básica para:

- Inicio de sesión de usuario (usuario y contraseña)
- Registro de horas por semana (horas `int`, comentario `string`)
- Guardar y consultar registros en CSV

## Compilación

```bash
make
```

## Ejecución

```bash
./bin/time-tracker
```

Los archivos `users.csv` y `entries.csv` se crean automáticamente si no existen.

## Formato de CSV

- `users.csv`

```csv
username,password,fullName
usuario1,pass123,Juan Perez
```

- `entries.csv`

```csv
username,year,isoWeek,hours,comment
usuario1,2025,50,8,Desarrollo de módulo de autenticación
```

## Notas

- Las contraseñas se guardan en texto plano en `users.csv` por simplicidad. Para uso real, utiliza hashing (ej. bcrypt/argon2) y no guardes la contraseña en claro.
- El cálculo de la semana ISO es una aproximación suficiente para la mayoría de los casos; para precisión total puedes usar una librería específica o ajustar el algoritmo.
- Los comentarios no se escapan de comas; si requieres comentarios con comas, adapta el almacenamiento para entrecomillar campos y manejar escapes.

CREATE TABLE Pacientes(
	folio_p serial PRIMARY KEY,
	nom_p text,
	edad_p int,
	sexo_p text check(sexo_p ~* '(femenino|masculino)'),
	fecha_registro date default now(),
	correo text UNIQUE,
	estado_p boolean default true	
);

CREATE TABLE Laboratoristas(
	cedula_lab text PRIMARY KEY,
	nom_lab text,
	fecha_nac_lab date,
	sexo_lab text,
	correo text UNIQUE,
	fecha_contratacion date default now(),	
	estado_lab boolean default true
);


CREATE TABLE Analisis(
	num_a serial PRIMARY KEY,
	nom_a text,
	tiempo_realizacion int
);

CREATE TABLE Historial_clinico(
	folio_a serial PRIMARY KEY,
	folio_p int REFERENCES Pacientes(folio_p),
	num_a int REFERENCES Analisis(num_a),
	status int,
	fecha date,
	cedula_lab text REFERENCES Laboratoristas(cedula_lab)	 
);


CREATE TABLE Materiales(
	codi_barra_m serial PRIMARY KEY,
	nom_m text,
	stock_max_m int,
	stock_min_m int,
	stock_actual_m int,
	estado_m boolean default true
);

CREATE TABLE Atributos(
	num_atri serial PRIMARY KEY,
	nom_atri text,
	descrip_atri text,
	min float,
	max float,
	estado_atri boolean default true
);

CREATE TABLE Unidad_medida(
	num_unidad serial PRIMARY KEY,
	nom_unidad text
);

CREATE TABLE Reactivos(
	codi_barra_r serial PRIMARY KEY,
	nom_r text,
	num_unidad int REFERENCES Unidad_medida(num_unidad),
	stock_max_r float,
	stock_min_r float,
	stock_actual_r float,
	estado_r boolean default true
);

CREATE TABLE Inventario_materiales(
	num_inv_m serial PRIMARY KEY,	
	fecha_inv_m date default now(),
	codi_barra_m int REFERENCES Materiales(codi_barra_m),
	stock_anterior_m int,
	stock_despues_m int,
	cant_ocupada_m int,
	folio_a int REFERENCES Historial_clinico(
	folio_a)
);

CREATE TABLE Inventario_reactivos(
	num_inv_r serial PRIMARY KEY,	
	fecha_inv_r date default now(),
	codi_barra_r int REFERENCES Reactivos(codi_barra_r),
	stock_anterior_r float,
	cant_ocupada_r float,
	stock_despues_r float,
	folia_a int REFERENCES Historial_clinico(folio_a)
);

CREATE TABLE Det_a_materiales(
	num_a int REFERENCES Analisis(num_a),
	cons_det_a_materiales int,
	codi_barra_m int REFERENCES Materiales(codi_barra_m),
	PRIMARY KEY(num_a,cons_det_a_materiales),
	cant_ocupada_m int
);

CREATE TABLE Det_a_atributos(
	num_a int REFERENCES Analisis(num_a),
	cons_det_a_atributos int,
	num_atri int REFERENCES Atributos(num_atri),
	PRIMARY KEY(num_a, cons_det_a_atributos)
);

CREATE TABLE Det_atributos(
	num_atri int REFERENCES Atributos(num_atri),
	cons_det_atributos int,
	codi_barra_r int REFERENCES Reactivos(codi_barra_r),
	PRIMARY KEY(num_atri, cons_det_atributos),
	cant_ocupada_r float
);

CREATE TABLE Resultados(
	folio_a int REFERENCES Historial_clinico(folio_a),
	cons_resultados int,
	resultado float,
	num_a int,
	cons_det_a_atributos int,
	FOREIGN KEY(num_a, cons_det_a_atributos) REFERENCES 
	Det_a_atributos(num_a, cons_det_a_atributos),
	num_atri int REFERENCES Atributos(num_atri),
	PRIMARY KEY(folio_a, cons_resultados)	
);

insert into unidad_medida(nom_unidad) values('Kg');
insert into unidad_medida(nom_unidad) values('Gr');
insert into unidad_medida(nom_unidad) values('Lt');
insert into unidad_medida(nom_unidad) values('Ml');

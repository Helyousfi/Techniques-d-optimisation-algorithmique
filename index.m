clc, clear all, close all
%% loading files to matrices
data_ds = readmatrix('mv_ds.xlsx');
data_fs = readmatrix('mv_fs.xlsx');
%% Comparaison des performances
%% Comparaison des sads
sadDs = zeros(1, 5680*23);
sadFs = zeros(1, 5680*23);
c = 1;
for i=1:5680
    for j=1:3:67
        sadFs(c) = data_fs(i,j);
        sadDs(c) = data_ds(i,j);
        c = c + 1;
    end
end
%Suppression des valeurs NaN
for i=1:5680*23
    if isnan(sadDs(i))
        sadDs(i) = 0;
    if isnan(sadFs(i))
        sadFs(i) = 0;
    end
    end
end
%compute sum of SADs
plot(sadDs - sadFs);
title("Différence des sadDs et sadFs de tous les blocs de chaque image");
differenceSad = sum(sadDs - sadFs);

sadDsMoy = zeros(1, 300);
sadFsMoy = zeros(1, 300);
c = 1;
for i=1:300
    MoyFS = 0;
    MoyDS = 0;
    for j=1:22*18
        MoyFS = MoyFS + sadFs(c);
        MoyDS = MoyDS + sadDs(c);
        c = c + 1;
    end
    sadDsMoy(i) = MoyDS/22*18;
    sadFsMoy(i) = MoyFS/22*18;
end
figure
plot(1:300,sadDsMoy,1:300,sadFsMoy);
legend("sadDs","sadFs")
title("sad de chaque image de la video");

%% Comparaison des vecreurs
VectorDs = zeros(1, 5680*23);
VectorFs = zeros(1, 5680*23);
c = 1;
for i=1:5680
    for j=1:67
        if(mod(j-1,3))
            VectorFs(c) = data_fs(i,j);
            VectorDs(c) = data_ds(i,j);
            c = c + 1;
        end
    end
end

normVectorDs = zeros(1, 5680*23 / 2);
normVectorFs = zeros(1, 5680*23 / 2);
cpt = 1;
for i=1:2:5680*23
    normVectorDs(cpt) = sqrt(VectorDs(i)* VectorDs(i) + VectorDs(i+1)*VectorDs(i+1));
    normVectorFs(cpt) = sqrt(VectorFs(i)* VectorFs(i) + VectorFs(i+1)*VectorFs(i+1));
    cpt = cpt + 1;
end



%Suppression des valeurs NaN
for i=1:5680*23 / 2
    if isnan(normVectorDs(i))
        normVectorDs(i) = 0;
    if isnan(normVectorFs(i))
        normVectorFs(i) = 0;
    end
    end
end

vectDsMoy = zeros(1, 300);
vectFsMoy = zeros(1, 300);
c = 1;
for i=1:300
    MoyFS_V = 0;
    MoyDS_V = 0;
    for j=1:22*18/2
        MoyFS_V = MoyFS_V + normVectorFs(c);
        MoyDS_V = MoyDS_V + normVectorDs(c);
        c = c + 1;
    end
    vectDsMoy(i) = MoyDS_V/22*18;
    vectFsMoy(i) = MoyFS_V/22*18;
end
figure
plot(1:300,vectDsMoy,1:300,vectFsMoy);
legend("vectDsMoy","vectFsMoy")
title("Moyenne des Vecteurs de deplacement de chaque image de la video");

%compute sum of motion vectors
figure
plot(normVectorFs - normVectorDs);
title("Différence des normVectorFs et normVectorDs de tous les blocs de chaque image");
normVectorSum = sum(normVectorFs - normVectorDs);

%Calcul des itérations qui dépassent 16 dans le fichier ds 
% Augmenter le nombre maximum d'itération ne sert à rien puisqu'on a
% seulemnt 311 qui atteignent 311
nbrIteration = 0;
for i=1:2:5680*23
    if (abs(VectorDs(i)) + abs(VectorDs(i+1)) == 16)
        nbrIteration = nbrIteration + 1;
    end
end



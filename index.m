clc, clear all, close all
%% loading files to matrices
data_ds = readmatrix('mv_ds.xlsx');
data_fs = readmatrix('mv_fs.xlsx');
%% Comparaison des performances
differenceSad = 0;
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
%Delete NAN values
for i=1:5680*23
    if isnan(sadDs(i))
        sadDs(i) = 0;
    if isnan(sadFs(i))
        sadFs(i) = 0;
    end
    end
end
%compute sum of SADs
sumSads = sum(sadDs - sadFs);
�R�����g�y�[�p�[�̏�����͂����ʁC���������ʂ̎������s�����D
������ʂ���͉Ȗږ��ƍu�`�ԍ����猟�����邱�Ƃ��\�ɂ����D
�ǉ���ʂƂ��āC�w�Дԍ��C�����C�N���X��(�Ȗږ�)�C���t�C�A���P�[�g���C���z����͂��邱�Ƃ��\�ɂ����D


�����݌v�Ƃ��Ă͈ȉ��̂Ƃ���ł���D
final.html�ɏ���ǉ������ʂ�
final_index.html�ɏ������������ʂ����������D

final.html�ɓ��͂��ꂽ�l�����ꂼ��ϐ��Ɋi�[���C
insert.php�ŏ���ǉ�����悤�Ɏw�肷��D
���̓f�[�^�x�[�X�ŊǗ�����Ă���C�e�����f�[�^�x�[�X�ɒǉ����鏈�����s���D
�ǉ����@�Ƃ��āCINSERT INTO data�@VALUES(�l�c);�Ƃ����N�G�������s����悤�Ɏw�肷��D

�܂��Cfinal_index.html�ł́C�u�`�ԍ��C�N���X��(�u�`��)����͂���ƁC���̒l��search.php�ɑ���C���̒l���猟������悤�Ɏw�肷��D
�������͂��Ă��Ȃ��̂ɑ��M�{�^���������ƃG���[���\�������悤�ɗ�O�������s���C
�ǂ��炩�Е��������͂����ꍇ��OR�����C�������͂����ꍇ��AND�������s���悤�Ɏw�肷��D
��̓I�ɂ�
SELECT * FROM data WHERE classname="�l"�@OR�܂���AND�@classnum="�l";
�Ǝw�肷��D

�ȉ��Ƀf�[�^�x�[�X�̃e�[�u�������L�ڂ���D
�񖼁F�T�v�F��

kouginum: �u�`�񐔁F��1��Ȃ�1

gakusekinum�F�w�Дԍ��F99999999

name�F���O�F���������i�����j

classname:�N���X���i�Ȗږ��j�F�����������������i�u�`���j

day�F���t�F20180707

anketo1�`4:�A���P�[�g�F�P�`�T�̌ܒi�K���l
kansou�F���z�F������(�Q�O�O���ȓ��Ƃ���j


�쐬�����e�[�u�����

CREATE TABLE data(
  
kouginum int,
  
gakusekinum int,
  
name nchar(20),
  
classname nchar(100),
  
day datetime,
  
anketo1 int,
  
anketo2 int,
  
anketo3 int,
  
anketo4 int,
  
kansou nchar(200)

);


INSERT���̈��F
INSERT INTO data(
  
kouginum,
  
gakusekinum,
  
name,
  
classname,
  
day,
  
anketo1,
  
anketo2,
  
anketo3,
  
anketo4,
  
kansou

)VALUE(
  
"2",
  
"99999999",
  
"���������i�����j",
  
"�����������������i�u�`���j",
  
"20180723",
  
"1",
  
"1",
  
"1",
  
"1",
  
"�܂��܂��ł��B"
);


�Č����邽�߂̎菇
�P�D�f�[�^�x�[�X���쐬����D
�Q�D�e�[�u�����쐬����D(�f�[�^�x�[�X���C�e�[�u�����͔C�ӂ̕�����)
�e�[�u�����͏�L�ɋL�ڂ����ʂ�ł���D
�R�D����̃t�@�C���ꎮ��var/www/html���ɒu���D
�S�Dinsert.php�Csearch.php�̃N�G���̕������f�[�^�x�[�X�����ύX���Ă����D
�T�Dhttp://localhost/index.html���J���D
�U�D������͂��C���M�{�^���������Ǝ��y�[�W�Ńf�[�^�x�[�X�ɐڑ����܂����ƕ\�������ΐ����ł���D
�V�D�R�����g�y�[�p�[�Q�ƃ{�^���������ƌ�����ʂ������D
�W�D������͂��C��قǒǉ�������񂪕\�������ΐ����ł���D
�X�D�e�y�[�W�̖߂�{�^���������Ƃ�������̃y�[�W���\�������͂��ł���D

�ȏオ���s�菇�ł���D


/********************************************************************/
/*                                                                  */
/*    Program Id    :  cntl000.ec                                   */
/*                                                                  */
/*    Program Name  :  休日判定処理                                 */
/*                                                                  */
/*    処理概要      :  休日判定を行う                               */
/*                                                                  */
/*    引数          :  システム日付                                 */
/*                                                                  */
/*    戻り値        :  0:営業日                                     */
/*                     1:休　日                                     */
/*                                                                  */
/*    Written By    :  HEK                                          */
/*                                                                  */
/*    Date          :  1997/01/20                                   */
/*                                                                  */
/*    Update        :  1997/01/20                                   */
/*                                                                  */
/*  ※注意事項                                                      */
/*    データベース名は運用系／開発系とで変更が必要                  */
/*    運用系：mrkdb                                                 */
/*    開発系：tstdb                                                 */
/*                                                                  */
/*    Copyright (c) 1996. HiElecomKowa,Ltd. All Right Reserved	    */
/********************************************************************/
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>
#include	<time.h>
$include	sqlca;

void		sql_error();
char		sql_nm[30];

main(argc,	argv)
	int		argc;
	char	*argv[];
{
	char	i_ymd[9];
$	int	d_ymd;
$	char	e_kbn[2];
$	char    *db_name;


	if(argc != 2){
		exit(-1);
	}
	db_name = getenv( "DB_NAME" ) ? getenv( "DB_NAME" ) : "mrkdb";
	memcpy(i_ymd,	argv[1],	sizeof(i_ymd));
	d_ymd = atoi(i_ymd);

$WHENEVER	SQLERROR CALL sql_error;
									strcpy(sql_nm,"DATABASE");
$	DATABASE $db_name;
									strcpy(sql_nm,"SET LOCK MODE");
$	SET	LOCK MODE TO WAIT 60;
									strcpy(sql_nm,"SET ISOLATION");
$	SET	ISOLATION TO COMMITTED READ;
									strcpy(sql_nm,"BEGIN WORK");
$	BEGIN	WORK;

$WHENEVER	NOT FOUND CONTINUE;
									strcpy(sql_nm,"SELECT");
$	SELECT 営業日区分 INTO $e_kbn FROM 営業日 
			WHERE 年月日 = $d_ymd;
									printf("営業日区分=%s\n",e_kbn);
/*
									printf("営業日区分=%s\n",e_kbn,SQLCODE);*/
									strcpy(sql_nm,"COMMIT WORK");
$	COMMIT	WORK;
	if ( e_kbn[0] == '0' ) {
		exit(1);
	}
	exit(0);
}
/********************************************************************/
/* SQL ERROR														*/
/********************************************************************/
void sql_error()
{
	int		ret_length = 0;
	char	errmsg[400];

	rgetlmsg(SQLCODE,errmsg,sizeof(errmsg),&ret_length);
	fprintf(stderr,
		"%s:%sでエラー発生！！。エラー番号 %d : %s\n",
		__FILE__,sql_nm, SQLCODE, errmsg);
	if (sqlca.sqlerrd[1] != 0) {
		rgetlmsg(sqlca.sqlerrd[1],errmsg,sizeof(errmsg),&ret_length);
		fprintf(stderr,
			"ＩＳＡＭコード %d : %s\n",
			sqlca.sqlerrd[1], errmsg);
	}
$	WHENEVER ERROR CONTINUE;
$	ROLLBACK WORK;
/*	exit(-1);   20040622  ｶﾘｼｮﾁ   */
  	exit(1);
}

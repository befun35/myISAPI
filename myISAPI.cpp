#include "stdafx.h"



/*
	return a pointer as pByte, and options such as length

*/
LPBYTE ISAPI_PrepareHttpFile(CString ePathWebSite, CString PathName, LPBYTE lpSrcData, int *p_iLenByte, int *p_iResult, CString *strStatu)
{
	CString str, str1;
//	int iReceived;
	int iResult = 0;
	UINT fLen;
	
	//
	LPBYTE pByteFile = NULL;	int iLenByte = 0;	//CString strFile;		CString strStatu;
	FRAMEDATA thisHeadSend;

/*	if (0)
	{
				CString sOutContent;
				
				sOutContent += "<html><body>\r\n" ;
				sOutContent += "<hr>This is a response <b>message</b> in HTML format. <font color=red>Wow!</font><hr>\r\n";
				sOutContent += m_Dlg->GlobalTime;
				sOutContent += "</body></html>";

	//			iResult = PrePareOutBuf_FromStringToChar(sOutContent);

	}
*/
	if(1)
	{
				iResult = 200;
				*strStatu = "OK";
				CFile fileDownload;

				// Oh_No
				// 
				PathName = ePathWebSite +  PathName;

PrepareHttpFileAgain404:
				if(!fileDownload.Open(PathName, CFile::modeRead))
				{
					iResult = error_Not_Found;
					*strStatu = str_error_Not_Found;

					PathName = ePathFileCommon404;
					goto PrepareHttpFileAgain404;
	//				return ;
				}
				else
				{
					fLen = (UINT)fileDownload.GetLength ();
					if ( fLen==0 )
					{
						//fileDownload.Close();
		//				iResult = 0;
		//				return;
					}
					else
					{
						pByteFile = (LPBYTE)LocalAlloc(LPTR, (int)(fLen+1));
						if( pByteFile == NULL )
						{
							AfxMessageBox(_T("LocalAlloc failed"));
							//fileDownload.Close();
							//
							iResult = error_Internal_Server_Error;
							*strStatu = str_error_Internal_Server_Error;
			//				return;
						}
						if ( fLen != fileDownload.Read( pByteFile, (int)fLen ) )
						{
							LocalFree(pByteFile);	pByteFile = NULL;
							iResult = error_Internal_Server_Error;
							*strStatu = str_error_Internal_Server_Error;
				//			return ;
						}
					}
					iLenByte = fLen;
					fileDownload.Close();
				}


				int iPosExtName = PathName.Find(_T(".json"));
				if (-1!=iPosExtName)
				{
/*					char *pdest;
					char str[] = "####";
					char string[1000] = "The quick brown dog jumps over the lazy fox";
					pdest = strstr( (char*)pByteFile, str );
*/
					//Add your data code here!!!!
					LPBYTE pByteFileNew = (LPBYTE)LocalAlloc(LPTR, (int)(fLen + 100) );
					sprintf( (char*)pByteFileNew, (char*)pByteFile
						);

					LocalFree(pByteFile);	pByteFile = pByteFileNew;
					iLenByte = fLen = strlen((char*)pByteFileNew);

				}
				

				

				if (iResult>=0)
				{
					//return 
					{
						thisHeadSend.FrameType = iDownloadFile;
						thisHeadSend.FromID = 0;
						thisHeadSend.ToID = 0;//thisHeadRecived.FromID;
						thisHeadSend.Seq = 0;
						thisHeadSend.SubSeq = 0;
						thisHeadSend.DataLen = fLen;
					}

				}
				else
				{
					//return 
					{
						thisHeadSend.FrameType = iDownloadFile;
						thisHeadSend.FromID = 0;
						thisHeadSend.ToID = 0;//thisHeadRecived.FromID;
						thisHeadSend.Seq = 0;
						thisHeadSend.SubSeq = 0;
						thisHeadSend.DataLen = iResult;
					}

				}
	}
		
	//return 
	*p_iResult = iResult;
	*p_iLenByte = iLenByte;
	return pByteFile;
}

USE [PS_GameData]
GO

/****** Object:  StoredProcedure [dbo].[usp_Read_User_CashPoint_UsersMaster]    Script Date: 1/12/2021 12:15:09 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON 
GO

CREATE Proc [dbo].[usp_Read_User_CashPoint_UsersMaster]  

@CashPoint int OUTPUT,
@UserUID int

AS

SET NOCOUNT ON

SET @CashPoint = 0

SELECT @CashPoint = ISNULL(Point, 0) FROM PS_UserData.dbo.Users_Master WHERE UserUID = @UserUID 

IF @CashPoint < 0
BEGIN
	UPDATE PS_UserData.dbo.Users_Master SET Point = 0 WHERE UserUID = @UserUID
	SET @CashPoint = 0
END

SET NOCOUNT OFF

GO

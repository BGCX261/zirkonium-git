/*	Copyright � 2007 Apple Inc. All Rights Reserved.
	
	Disclaimer: IMPORTANT:  This Apple software is supplied to you by 
			Apple Inc. ("Apple") in consideration of your agreement to the
			following terms, and your use, installation, modification or
			redistribution of this Apple software constitutes acceptance of these
			terms.  If you do not agree with these terms, please do not use,
			install, modify or redistribute this Apple software.
			
			In consideration of your agreement to abide by the following terms, and
			subject to these terms, Apple grants you a personal, non-exclusive
			license, under Apple's copyrights in this original Apple software (the
			"Apple Software"), to use, reproduce, modify and redistribute the Apple
			Software, with or without modifications, in source and/or binary forms;
			provided that if you redistribute the Apple Software in its entirety and
			without modifications, you must retain this notice and the following
			text and disclaimers in all such redistributions of the Apple Software. 
			Neither the name, trademarks, service marks or logos of Apple Inc. 
			may be used to endorse or promote products derived from the Apple
			Software without specific prior written permission from Apple.  Except
			as expressly stated in this notice, no other rights or licenses, express
			or implied, are granted by Apple herein, including but not limited to
			any patent rights that may be infringed by your derivative works or by
			other works in which the Apple Software may be incorporated.
			
			The Apple Software is provided by Apple on an "AS IS" basis.  APPLE
			MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
			THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
			FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND
			OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
			
			IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
			OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
			SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
			INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
			MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED
			AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
			STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
			POSSIBILITY OF SUCH DAMAGE.
*/
#if !defined(__HLAudioFile_h__)
#define __HLAudioFile_h__

//=============================================================================
//	Includes
//=============================================================================

#include "HLFile.h"
#include <AudioToolbox/AudioFile.h>

//=============================================================================
//	HLAudioFile
//=============================================================================

class HLAudioFile
:
	public HLFile
{

//	Construction/Destruction
public:
					HLAudioFile(const FSRef& inFSRef, UInt32 inATFileType, CFStringRef inNameExtension);
	virtual			~HLAudioFile();

//	Attributes
public:
	virtual void	SetType();
	virtual void	SetNameExtension();
	virtual void	GetFormat(AudioStreamBasicDescription& outFormat) const;
	
//	Operations
public:
	virtual void	Open(bool inForReading, bool inForWriting);
	virtual void	Close();

	virtual void	Prepare();
	virtual void	PrepareNew(const void* inData, UInt32 inDataSize);
	virtual void	Flush(bool inOptimizeLayout);
	
	virtual SInt64	GetRawByteSize() const;
	virtual void	SetRawByteSize(SInt64 inSize);
	
	virtual void	ReadRawBytes(SInt64 inOffset, UInt32& ioNumberBytes, void* outData, bool inCache = true);
	virtual void	WriteRawBytes(SInt64 inOffset, UInt32& ioNumberBytes, void* inData, bool inCache = true);

	virtual SInt64	GetAudioByteSize() const;
	virtual void	SetAudioByteSize(SInt64 inSize);
	
	virtual void	ReadAudioBytes(SInt64 inOffset, UInt32& ioNumberBytes, void* outData, bool inCache = true);
	virtual void	WriteAudioBytes(SInt64 inOffset, UInt32& ioNumberBytes, void* inData, bool inCache = true);

	virtual SInt64	GetAudioFrameSize() const;
	virtual void	SetAudioFrameSize(SInt64 inSize);
	
	virtual void	ReadAudioFrames(SInt64 inOffset, UInt32& ioNumberFrames, void* outData, bool inCache = true);
	virtual void	WriteAudioFrames(SInt64 inOffset, UInt32& ioNumberFrames, void* inData, bool inCache = true);

//	Implementation
protected:
	AudioFileID		mAudioFileID;
	UInt32			mATFileType;
	CFStringRef		mNameExtension;
	AudioStreamBasicDescription	mFormat;

};

//=============================================================================
//	HLAudioFileFactory
//=============================================================================

class HLAudioFileFactory
:
	public HLFileFactory
{

//	Construction/Destruction
public:
								HLAudioFileFactory(UInt32 inATFileType, CFStringRef inNameExtension);
	virtual						~HLAudioFileFactory();

//	Operations
public:
	virtual bool				ObjectIsA_FSRef(const FSRef& inFSRef) const;
	virtual HLFileSystemObject*	Create_FSRef(const FSRef& inParentFSRef, CFStringRef inName, const void* inData, UInt32 inDataSize);

protected:
	virtual HLFile*				CreateObject(const FSRef& inFSRef);

};

#endif
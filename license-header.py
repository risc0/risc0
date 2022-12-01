#!/usr/bin/env python

# Tool license-header
#
# Copyright (C) 2022 Wang Qi (wqking)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
import glob
import argparse
import traceback
import difflib

class Application :
	def __init__(self) :
		self._action = None
		self._sourcePatterns = []
		self._excludePatterns = []
		self._licenseFile = None
		self._before = ''
		self._after = ''
		self._lineBefore = ''
		self._lineAfter = ''
		self._licenseLines = []

	def run(self) :
		try :
			self._parseCommandLine(sys.argv[1:])
			self._doRun()
		except Exception as e:
			traceback.print_exc()

	def _unescapeText(self, text) :
		if text is None :
			return text;
		text = text.replace("\\n", "\n")
		return text

	def _doRun(self) :
		self._before = self._unescapeText(self._before)
		self._after = self._unescapeText(self._after)

		with open(self._licenseFile, 'r') as f :
			licenseLines = f.readlines()
		lastEmptyLineIndex = len(licenseLines)
		for i in range(len(licenseLines) - 1, -1, -1) :
			line = licenseLines[i]
			line = line.strip()
			if line != '' :
				break
			lastEmptyLineIndex = i
		if lastEmptyLineIndex < len(licenseLines) :
			licenseLines = licenseLines[0 : lastEmptyLineIndex]
		self._licenseLines = []
		if self._before is not None :
			self._licenseLines.append(self._before + "\n")
		for line in licenseLines :
			if self._lineBefore is not None :
				line = self._lineBefore + line
			if self._lineAfter is not None :
				line = line + self._lineAfter
			self._licenseLines.append(line)
		if self._after is not None :
			self._licenseLines.append(self._after + "\n")

		for sourcePattern in self._sourcePatterns :
			self._doOnSourcePattern(sourcePattern)

	def _doOnSourcePattern(self, sourcePattern) :
		fileList = glob.glob(sourcePattern, recursive = True)
		for file in fileList :
			self._doOnFile(file)

	def _doOnFile(self, file) :
		if not self._canProcessFile(file) :
			return
		with open(file, 'r') as f :
			sourceLine = f.readlines()
		tempLineList = self._doRemoveLicense(sourceLine)
		lineList = []
		for line in tempLineList :
			if len(lineList) == 0 :
				if line.strip() == '' :
					continue
			lineList.append(line)
		if self._action == 'update' :
			lineList = self._licenseLines + lineList
		if not self._isSameList(sourceLine, lineList) :
			with open(file, 'w') as f :
				f.writelines(lineList)

	def _canProcessFile(self, file) :
		for exclude in self._excludePatterns :
			if exclude in file :
				return False
		return True

	def _isSameList(self, a, b) :
		if len(a) != len(b) :
			return False
		for i in range(len(a)) :
			if a[i] != b[i] :
				return False
		return True

	def _doRemoveLicense(self, lineList) :
		matchedLineCount = self._doGetMatchedLicenseLineCount(lineList)
		if matchedLineCount > 0 :
			resultList = lineList[matchedLineCount : ]
		else :
			resultList = lineList + []
		return resultList

	def _doGetMatchedLicenseLineCount(self, lineList) :
		if len(lineList) < len(self._licenseLines) :
			return 0;
		maxLineCount = len(self._licenseLines) + 10
		for i in range(maxLineCount - 1, 0, -1) :
			if i >= len(lineList) :
				continue
			if self._doLineMatchLicense(lineList[i]) :
				return i + 1
		return 0

	def _doLineMatchLicense(self, a) :
		if a.strip() == '' :
			return False
		for line in self._licenseLines :
			if self._doLineMatch(a, line) :
				return True
		return False

	def _doLineMatch(self, a, b) :
		a = self._doNormalizeLineForMatch(a)
		b = self._doNormalizeLineForMatch(b)
		if len(a) < 10 :
			return False
		ratio = difflib.SequenceMatcher(None, a, b).ratio()
		return ratio >= 0.6

	def _doNormalizeLineForMatch(self, line) :
		line = line.replace(" ", "")
		line = line.replace("\t", "")
		return line

	def _parseCommandLine(self, commandLineArguments) :
		parser = argparse.ArgumentParser(add_help = False)
		parser.add_argument('--help', action = 'store_true', help = 'Show help message')
		parser.add_argument('-h', action = 'store_true', dest = 'help', help = 'Show help message')
		parser.add_argument('action', help = "The action, can be update or remove", default = 'update', choices = [ 'update', 'remove' ])
		parser.add_argument('--source', action = 'append', required = True, help = "The source file patterns, can have path and wildcard")
		parser.add_argument('--license', required = True, help = "The license file location")
		parser.add_argument('--before', required = False, help = "The text added before the license block", default = None)
		parser.add_argument('--after', required = False, help = "The text added after the license block", default = None)
		parser.add_argument('--line-before', required = False, help = "The text added before each line", default = None)
		parser.add_argument('--line-after', required = False, help = "The text added after each line", default = None)
		parser.add_argument('--exclude', action = 'append', required = False, help = "The patterns to exclude, can not have wildcard")

		options = parser.parse_args(commandLineArguments)
		options = vars(options)
		#print(options)

		if options['help'] :
			self._showUsage(parser)
			return False

		self._action = options['action']
		self._sourcePatterns = options['source']
		self._licenseFile = options['license']
		self._before = options['before']
		self._after = options['after']
		self._lineBefore = options['line_before']
		self._lineAfter = options['line_after']
		self._excludePatterns = options['exclude']
		if self._excludePatterns is None :
			self._excludePatterns = []

	def _showUsage(self, parser) :
		parser.print_help()


Application().run()

#pragma once

class NoCopy {
public:
	NoCopy(const NoCopy&) = delete;
	const NoCopy& operator=(const NoCopy&) = delete;

protected:
	NoCopy() = default;
	~NoCopy() = default;
};


class NoConstruct {
public:
	NoConstruct() = delete;
	NoConstruct(const NoConstruct& other) = delete;
	const NoConstruct& operator=(const NoConstruct& other) = delete;

protected:
	~NoConstruct() = default;
};
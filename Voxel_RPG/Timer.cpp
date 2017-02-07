#include"Timer.h"

void Timer::start() {
	m_startTimePoint = m_clock.now();
	m_running = true;
}

void Timer::stop() {
	m_endTimePoint = m_clock.now();
	m_running = false;
}

double Timer::milliseconds() {
	if (m_running) {
		return (m_clock.now() - m_startTimePoint).count() * Timer::NANOSECONDS_TO_MILLISECONDS;
	}
	else {
		return (m_endTimePoint - m_startTimePoint).count() * Timer::NANOSECONDS_TO_MILLISECONDS;
	}
}

double Timer::seconds() {
	if (m_running) {
		return (m_clock.now() - m_startTimePoint).count() * Timer::NANOSECONDS_TO_SECONDS;
	}
	else {
		return (m_endTimePoint - m_startTimePoint).count() * Timer::NANOSECONDS_TO_SECONDS;
	}
}

void Timer::updateStart() {
	if (m_running) {
		m_startTimePoint = m_clock.now();
	}
}
#pragma once

// Operations boss.

#include <BWAPI.h>
#include "UnitData.h"

namespace UAlbertaBot
{
	class The;
	struct UnitInfo;

	enum class ClusterStatus
	{
		None          // enemy cluster or not updated yet
		, Advance     // no enemy near, moving forward
		, Attack      // enemy nearby, attacking
		, Regroup     // regrouping (usually retreating)
		, FallBack    // returning to base
	};

	class UnitCluster
	{
	public:
		BWAPI::Position center;
		int radius;
		ClusterStatus status;

		bool air;
		double speed;

		size_t count;
		int hp;
		double groundDPF;		// DPF = damage per frame
		double airDPF;

		BWAPI::Unitset units;

		UnitCluster();

		void clear();
		void add(const UnitInfo & ui);
		size_t size() const { return count; };
		void draw(BWAPI::Color color, const std::string & label = "") const;
	};

	class OpsBoss
	{
		const int clusterStart = 5 * 32;
		const int clusterRange = 3 * 32;

		std::vector<UnitCluster> yourClusters;

		void locateCluster(const std::vector<BWAPI::Position> & points, UnitCluster & cluster);
		void formCluster(const UnitInfo & seed, const UIMap & theUI, BWAPI::Unitset & units, UnitCluster & cluster);
		void clusterUnits(BWAPI::Unitset & units, std::vector<UnitCluster> & clusters);

	public:
		OpsBoss();
		void initialize();

		void cluster(BWAPI::Player player, std::vector<UnitCluster> & clusters);
		void cluster(const BWAPI::Unitset & units, std::vector<UnitCluster> & clusters);

		void update();

		void drawClusters() const;
	};
}
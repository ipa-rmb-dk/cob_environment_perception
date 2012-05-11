/****************************************************************
 *
 * Copyright (c) 2011
 *
 * Fraunhofer Institute for Manufacturing Engineering
 * and Automation (IPA)
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Project name: care-o-bot
 * ROS stack name: cob_environment_perception_intern
 * ROS package name: cob_3d_mapping_features
 * Description:
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Author: Steffen Fuchs, email:georg.arbeiter@ipa.fhg.de
 * Supervised by: Georg Arbeiter, email:georg.arbeiter@ipa.fhg.de
 *
 * Date of creation: 04/2012
 * ToDo:
 *
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Fraunhofer Institute for Manufacturing
 *       Engineering and Automation (IPA) nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License LGPL as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License LGPL for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License LGPL along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************/

#ifndef __COB_3D_MAPPING_FEATURES_CLUSTER_HANDLER_H__
#define __COB_3D_MAPPING_FEATURES_CLUSTER_HANDLER_H__

#include <cob_3d_mapping_common/point_types.h>
#include <cob_3d_mapping_common/label_defines.h>
#include "cob_3d_mapping_features/cluster_types.h"

#include <list>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/eigen.h>


namespace cob_3d_mapping_features
{
  template<typename ClusterT>
  class ClusterHandlerBase
  {
  public:
    typedef ClusterT ClusterType;
    typedef typename std::list<ClusterT>::iterator ClusterPtr;
    typedef typename std::list<ClusterT>::reverse_iterator reverse_iterator;
    typedef typename std::list<ClusterT>::size_type size_type;

  public:
    ClusterHandlerBase() : clusters_()
      , id_to_cluster_()
      , max_cid_(0)
      , color_tab_()
    {
      const float rand_max_inv = 1.0f/ RAND_MAX;
      color_tab_.reserve(2052);
      color_tab_.push_back( (  0 << 16 |   0 << 8 | 255) ); // edge
      color_tab_.push_back( (255 << 16 | 200 << 8 |   0) ); // first
      color_tab_.push_back( (  0 << 16 | 200 << 8 | 255) ); // first
      color_tab_.push_back( (  0 << 16 | 200 << 8 |   0) ); // first
      for (size_t i=0; i<2048; ++i)
      {
	int r = (float)rand() * rand_max_inv * 255;
	int g = (float)rand() * rand_max_inv * 255;
	int b = (float)rand() * rand_max_inv * 255;
	color_tab_.push_back( r << 16 | g << 8 | b );
      }
    }
    virtual ~ClusterHandlerBase() { };

    inline ClusterPtr begin() { return clusters_.begin(); }
    inline ClusterPtr end() { return clusters_.end(); }
    inline reverse_iterator rbegin() { return clusters_.rbegin(); }
    inline reverse_iterator rend() { return clusters_.rend(); }
    inline std::pair<ClusterPtr,ClusterPtr> getClusters() { return std::make_pair(clusters_.begin(),clusters_.end()); }
    inline std::pair<reverse_iterator, reverse_iterator> getClustersReverse() 
    { return std::make_pair(clusters_.rbegin(), clusters_.rend()); }
    inline size_type numClusters() const { return clusters_.size(); }
    inline void sortBySize() { clusters_.sort(); }
    virtual void clear() { clusters_.clear(); id_to_cluster_.clear(); max_cid_ = 0; }

    inline ClusterPtr getCluster(const int id) { return id_to_cluster_[id]; }
    inline ClusterPtr createCluster(int id = 0)
    { 
      clusters_.push_back(ClusterType( (id<=max_cid_ ? ++max_cid_ : max_cid_ = id) )); 
      return (id_to_cluster_[id] = --clusters_.end());
    }
    inline void getColoredCloud(pcl::PointCloud<PointXYZRGB>::Ptr color_cloud)
    {
      uint32_t rgb; int t = 1;
      for(reverse_iterator c = clusters_.rbegin(); c != clusters_.rend(); ++c, ++t)
      {
	if (c->id() == I_NAN || c->id() == I_BORDER) { rgb = color_tab_[0]; --t; }
	else { rgb = color_tab_[t]; }
	for(size_t i = 0; i<c->size(); ++i) { color_cloud->points[(*c)[i]].rgb = *reinterpret_cast<float*>(&rgb); }
      }
    }

    virtual void addPoint(ClusterPtr c, int idx) = 0;
    virtual void merge(ClusterPtr source, ClusterPtr target) = 0;

  private:
    std::list<ClusterType> clusters_;
    std::map<int,ClusterPtr> id_to_cluster_;
    int max_cid_;
    std::vector<int> color_tab_;
  };


  template<typename LabelT, typename PointT, typename PointNT>
  class DepthClusterHandler : public ClusterHandlerBase<DepthCluster>
  {
  public:
    typedef boost::shared_ptr<DepthClusterHandler<LabelT,PointT,PointNT> > Ptr;

    typedef pcl::PointCloud<LabelT> LabelCloud;
    typedef typename LabelCloud::ConstPtr LabelCloudConstPtr;
    typedef pcl::PointCloud<PointT> PointCloud;
    typedef typename PointCloud::ConstPtr PointCloudConstPtr;
    typedef pcl::PointCloud<PointNT> NormalCloud;
    typedef typename NormalCloud::ConstPtr NormalCloudConstPtr;

  public:
    DepthClusterHandler()
    { };
    ~DepthClusterHandler() { };

    void addPoint(ClusterPtr c, int idx)
    { 
      c->addIndex(idx);
      c->sum_points_ += surface_->points[idx].getVector3fMap();
      c->sum_orientations_ += normals_->points[idx].getNormalVector3fMap();
    }

    inline void merge(ClusterPtr source, ClusterPtr target)
    { for (ClusterType::iterator idx = source->begin(); idx != source->end(); ++idx) addPoint(target, *idx); }

    inline void setLabelCloud(LabelCloudConstPtr labels) { labels_ = labels; }
    inline void setPointCloud(PointCloudConstPtr points) { surface_ = points; }
    inline void setNormalCloud(NormalCloudConstPtr normals) { normals_ = normals; }

    void computeClusterComponents(ClusterPtr c);
    void computeCurvature(ClusterPtr c);
    void computePointCurvature(ClusterPtr c, int search_size);
    bool computePrincipalComponents(ClusterPtr c);
    void computeNormalIntersections(ClusterPtr c);
    //void computeColorHistogram(ClusterPtr c);
    void recomputeClusterNormals(ClusterPtr c);

  private:
    LabelCloudConstPtr labels_;
    PointCloudConstPtr surface_;
    NormalCloudConstPtr normals_;
  };

}

#endif

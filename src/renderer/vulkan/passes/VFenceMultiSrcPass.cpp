#include "renderer/vulkan/passes/VFenceMultiSrcPass.hpp"

namespace sge::vulkan {

VFenceMultiSrcPass::VFenceMultiSrcPass(VRendererBackend* renderer,
                                       const std::string name, const u32 count)
    : RenderPass(renderer, name, false),
      m_fencesSource(source<std::vector<fence>>("fences")),
      m_fences([&]() {
        std::vector<fence> fences(count);
        for (u32 i = 0; i < count; i++) {
          fences[i] = m_vrenderer->createFence();
        }
        return fences;
      }()) {
  registerSource(&m_fencesSource);
  m_fencesSource.set(&m_fences);
}

void VFenceMultiSrcPass::recreate() {
  for (u32 i = 0; i < m_fences.size(); i++) {
    m_vrenderer->destroyFence(m_fences[i]);
    m_fences[i] = m_vrenderer->createFence();
  }
}

void VFenceMultiSrcPass::dispose() {
  m_fencesSource.reset();
  for (const fence fence : m_fences) {
    m_vrenderer->destroyFence(fence);
  }
}

}  // namespace sge::vulkan

#pragma once

#include <set>
#include <string>
#include <vector>

#include "renderer/RenderPass.hpp"
#include "renderer/Renderer.hpp"
#include "types/inttypes.hpp"

namespace sge {

class Rendergraph : public RenderPass {
 public:
  Rendergraph(RendererBackend* renderer, const std::string name);

  virtual void create() override;
  virtual void recreate() override;
  virtual void beginFrame() override;
  virtual void execute() override;
  virtual void endFrame() override;
  virtual void dispose() override;

 protected:
  void addLinkage(const std::string& source, const std::string& sink);

  template <class RenderPass_t>
  RenderPass_t& getPassById(u32 pass_id) {
    assert(pass_id <= m_passes.size());
    return *reinterpret_cast<RenderPass_t*>(m_passes[pass_id].get());
  }
  template <class RenderPass_t, typename... Args>
  u32 createPass(Args&&... args) {
    m_passes.push_back(
        std::make_unique<RenderPass_t>(std::forward<Args>(args)...));
    return m_passes.size() - 1;
  }
  RenderPass& getPassById(u32 pass_id);
  RenderPass& getPassByName(const std::string name);

  u32 getPassIdByName(const std::string name);
  void markPassAsRoot(const u32 passId);
  void unmarkPassAsRoot(const u32 passId);
  void build();
  void scheduleRecreation() { m_requireRecreation = true; }

 private:
  struct linkage {
    u32 m_sourcePassId;
    std::string m_sourceName;
    u32 m_sinkPassId;
    std::string m_sinkName;
  };
  boolean m_requireRecreation = false;
  std::vector<linkage> m_linkages;
  std::vector<u32> m_dependencyOrder;
  std::vector<u32> m_execution_order;
  std::vector<std::unique_ptr<RenderPass>> m_passes;
  std::vector<u32> m_rootPassIds;
  boolean m_is_deprecated = true;
};

}  // namespace sge

function Monster.getMonster(self)
	return self:isMonster() and self or nil
end

function Monster.isItem(self)
	return false
end

function Monster.isMonster(self)
	return true
end

function Monster.isNpc(self)
	return false
end

function Monster.isPlayer(self)
	return false
end

function Monster.isTile(self)
	return false
end

function Monster.isContainer(self)
	return false
end
